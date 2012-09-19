/* File:      system_xsb.c
** Author(s): David S. Warren, Jiyang Xu, Kostis F. Sagonas, kifer
** Contact:   xsb-contact@cs.sunysb.edu
** 
** Copyright (C) The Research Foundation of SUNY, 1986, 1993-1999
** Copyright (C) ECRC, Germany, 1990
** 
** XSB is free software; you can redistribute it and/or modify it under the
** terms of the GNU Library General Public License as published by the Free
** Software Foundation; either version 2 of the License, or (at your option)
** any later version.
** 
** XSB is distributed in the hope that it will be useful, but WITHOUT ANY
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for
** more details.
** 
** You should have received a copy of the GNU Library General Public License
** along with XSB; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
** $Id: system_xsb.c,v 1.31.2.1 2003/06/23 20:01:34 lfcastro Exp $
** 
*/

#include "xsb_config.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>


#ifdef WIN_NT
#include <windows.h>
#include <direct.h>
#include <io.h>
#include <process.h>
#include <winbase.h>
#else
#include <unistd.h>	
#include <stddef.h>
#include <sys/wait.h>
#include <dirent.h>
#endif

#include <fcntl.h>

#include "auxlry.h"
#include "cell_xsb.h"
#include "error_xsb.h"
#include "cinterf.h"
#include "syscall_xsb.h"
#include "io_builtins_xsb.h"
/* wind2unix.h must be included after sys/stat.h */
#include "wind2unix.h"
#include "system_xsb.h"
#include "system_defs_xsb.h"
#include "register.h"
#include "psc_xsb.h"

#define MAX_CMD_LEN 1024

static int xsb_spawn (char *prog, char *arg[], int callno,
		      int pipe1[], int pipe2[], int pipe3[],
		      FILE *toprocess_fptr, FILE *fromprocess_fptr,
		      FILE *fromproc_stderr_fptr);
static void concat_array(char *array[], char *separator,
			 char *result_str, int maxsize);
static int get_free_process_cell(void);
static void init_process_table(void);
static int process_status(int pid);
static void split_command_arguments(char *string, char *params[], char *callname);
static char *get_next_command_argument(char **buffptr, char **cmdlineprt);


static struct proc_table_t {
  int search_idx;	       /* index where to start search for free cells */
  struct proc_array_t {
    int pid;
    int to_stream;     	       /* XSB stream to process stdin    */
    int from_stream;           /* XSB stream from process stdout */
    int stderr_stream;	       /* XSB stream from process stderr */
    char cmdline[MAX_CMD_LEN];  /* the cmd line used to invoke the process */
  } process[MAX_SUBPROC_NUMBER];
} xsb_process_table;

static xsbBool file_stat(int callno, char *file);

static int xsb_find_first_file(prolog_term, char*, prolog_term);
static int xsb_find_next_file(prolog_term, char*, prolog_term);

int sys_syscall(int callno)
{
  int result=-1;
  struct stat stat_buff;

  switch (callno) {
  case SYS_exit: {
    int exit_code;
    exit_code = ptoc_int(3);
    xsb_mesg("\nXSB exited with exit code: %d", exit_code);
    exit(exit_code); break;
  }
#if (!defined(WIN_NT))
  case SYS_getpid : result = getpid(); break; 
  case SYS_link  : result = link(ptoc_longstring(3), ptoc_longstring(4)); break;
#endif
  case SYS_mkdir: {
#ifndef WIN_NT
    /* create using mode 700 */
    result = mkdir(ptoc_longstring(3), 0700); 
#else
    result = _mkdir(ptoc_longstring(3)); 
#endif
    break;
  }
  case SYS_rmdir: {
#ifndef WIN_NT
    result = rmdir(ptoc_longstring(3)); 
#else
    result = _rmdir(ptoc_longstring(3)); 
#endif
    break;
  }
  case SYS_unlink: result = unlink(ptoc_longstring(3)); break;
  case SYS_chdir : result = chdir(ptoc_longstring(3)); break;
  case SYS_access: {
    switch(*ptoc_string(4)) {
    case 'r': /* read permission */
      result = access(ptoc_longstring(3), R_OK_XSB);
      break;
    case 'w': /* write permission */
      result = access(ptoc_longstring(3), W_OK_XSB);
      break;
    case 'x': /* execute permission */
      result = access(ptoc_longstring(3), X_OK_XSB);
      break;
    default:
      result = -1;
    }
    break;
  }
  case SYS_stat  : {
    /* Who put this in??? What did s/he expect to get out of this call?
       stat_buff is never returned (and what do you do with it in Prolog?)!!!
    */
    result = stat(ptoc_longstring(3), &stat_buff);
    break;
  }
  case SYS_rename: result = rename(ptoc_longstring(3), ptoc_longstring(4)); break;
  case SYS_cwd: {
    char current_dir[MAX_CMD_LEN];
    /* returns 0, if != NULL, 1 otherwise */
    result = (getcwd(current_dir, MAX_CMD_LEN-1) == NULL);
    if (result == 0)
      ctop_string(3,string_find(current_dir,1));
    break;
  }
  default: xsb_abort("[SYS_SYSCALL] Unknown system call number, %d", callno);
  }
  return result;
}

xsbBool sys_system(int callno)
{
  int pid;

  switch (callno) {
  case PLAIN_SYSTEM_CALL: /* dumb system call: no communication with XSB */
    /* this call is superseded by shell and isn't used */
    ctop_int(3, system(ptoc_string(2)));
    return TRUE;
  case SLEEP_FOR_SECS:
#ifdef WIN_NT
    Sleep(ptoc_int(2) * 1000);
#else
    sleep(ptoc_int(2));
#endif
    return TRUE;
  case GET_TMP_FILENAME:
    ctop_string(2,string_find(tmpnam(NULL),1));
    return TRUE;
  case IS_PLAIN_FILE:
  case IS_DIRECTORY:
  case STAT_FILE_TIME:
  case STAT_FILE_SIZE:
    return file_stat(callno, ptoc_longstring(2));
  case EXEC: {
#ifdef HAVE_EXECVP
    /* execs a new process in place of XSB */
    char *params[MAX_SUBPROC_PARAMS+2];
    prolog_term cmdspec_term;
    int index = 0;
    
    cmdspec_term = reg_term(2);
    if (islist(cmdspec_term)) {
      prolog_term temp, head;
      char *string_head=NULL;

      if (isnil(cmdspec_term))
	xsb_abort("[exec] Arg 1 must not be an empty list.");
      
      temp = cmdspec_term;
      do {
	head = p2p_car(temp);
	temp = p2p_cdr(temp);
	if (isstring(head)) 
	  string_head = string_val(head);
	else
	  xsb_abort("[exec] non-string argument passed in list.");
	
	params[index++] = string_head;
	if (index > MAX_SUBPROC_PARAMS)
	  xsb_abort("[exec] Too many arguments.");
      } while (!isnil(temp));
      params[index] = NULL;
    } else if (isstring(cmdspec_term)) {
      char *string = string_val(cmdspec_term);
      split_command_arguments(string, params, "exec");
    } else
      xsb_abort("[exec] 1st argument should be term or list of strings.");

    if (execvp(params[0], params)) 
      xsb_abort("[exec] Exec call failed.");
#else
    xsb_abort("[exec] builtin not supported in this architecture.");
#endif
  }
    
  case SHELL: /* smart system call: like SPAWN_PROCESS, but returns error code
		 instead of PID. Uses system() rather than execvp.
		 Advantage: can pass arbitrary shell command. */
  case SPAWN_PROCESS: { /* spawn new process, reroute stdin/out/err to XSB */
    /* +CallNo=2, +ProcAndArgsList,
       -StreamToProc, -StreamFromProc, -StreamFromProcStderr,
       -Pid */
    static int pipe_to_proc[2], pipe_from_proc[2], pipe_from_stderr[2];
    int toproc_stream=-1, fromproc_stream=-1, fromproc_stderr_stream=-1;
    int pid_or_status;
    FILE *toprocess_fptr=NULL,
      *fromprocess_fptr=NULL, *fromproc_stderr_fptr=NULL;
    char *params[MAX_SUBPROC_PARAMS+2]; /* one for progname--0th member,
				       one for NULL termination*/
    prolog_term cmdspec_term, cmdlist_temp_term;
    prolog_term cmd_or_arg_term;
    xsbBool toproc_needed=FALSE, fromproc_needed=FALSE, fromstderr_needed=FALSE;
    char *cmd_or_arg=NULL, *shell_cmd=NULL;
    int idx = 0, tbl_pos;
    char *callname=NULL;
    xsbBool params_are_in_a_list=FALSE;

    init_process_table();

    if (callno == SPAWN_PROCESS)
      callname = "SPAWN_PROCESS";
    else
      callname = "SHELL";

    cmdspec_term = reg_term(2);
    if (islist(cmdspec_term))
      params_are_in_a_list = TRUE;
    else if (isstring(cmdspec_term))
      shell_cmd = string_val(cmdspec_term);
    else
      xsb_abort("[%s] Arg 1 must be an atom or a list [command, arg, ...]",
		callname);

    /* the user can indicate that he doesn't want either of the streams created
       by putting an atom in the corresponding argument position */
    if (isref(reg_term(3)))
      toproc_needed = TRUE;
    if (isref(reg_term(4)))
      fromproc_needed = TRUE;
    if (isref(reg_term(5)))
      fromstderr_needed = TRUE;

    /* if any of the arg streams is already used by XSB, then don't create
       pipes --- use these streams instead. */
    if (isinteger(reg_term(3))|isboxedinteger(reg_term(3))) {
      SET_FILEPTR(toprocess_fptr, int_val(reg_term(3)));
    }
    if (isinteger(reg_term(4))|isboxedinteger(reg_term(4))) {
      SET_FILEPTR(fromprocess_fptr, int_val(reg_term(4)));
    }
    if (isinteger(reg_term(5))|isboxedinteger(reg_term(5))) {
      SET_FILEPTR(fromproc_stderr_fptr, int_val(reg_term(5)));
    }

    if (!isref(reg_term(6)))
      xsb_abort("[%s] Arg 5 (process id) must be a variable", callname);

    if (params_are_in_a_list) {
      /* fill in the params[] array */
      if (isnil(cmdspec_term))
	xsb_abort("[%s] Arg 1 must not be an empty list", callname);
      
      cmdlist_temp_term = cmdspec_term;
      do {
	cmd_or_arg_term = p2p_car(cmdlist_temp_term);
	cmdlist_temp_term = p2p_cdr(cmdlist_temp_term);
	if (isstring(cmd_or_arg_term)) {
	  cmd_or_arg = string_val(cmd_or_arg_term);
	}
	else 
	  xsb_abort("[%s] Non string list member in the Arg",
		    callname);
	
	params[idx++] = cmd_or_arg;
	if (idx > MAX_SUBPROC_PARAMS)
	  xsb_abort("[%s] Too many arguments passed to subprocess",
		    callname);
	
      } while (!isnil(cmdlist_temp_term));

      params[idx] = NULL; /* null termination */

    } else { /* params are in a string */
      if (callno == SPAWN_PROCESS)
	split_command_arguments(shell_cmd, params, callname);
      else {
	/* if callno==SHELL => call system() => don't split shell_cmd */
	params[0] = shell_cmd;
	params[1] = NULL;
      }
    }
    
    /* -1 means: no space left */
    if ((tbl_pos = get_free_process_cell()) < 0) {
      xsb_warn("Can't create subprocess because XSB process table is full");
      return FALSE;
    }

    /* params[0] is the progname */
    pid_or_status = xsb_spawn(params[0], params, callno,
			      (toproc_needed ? pipe_to_proc : NULL),
			      (fromproc_needed ? pipe_from_proc : NULL),
			      (fromstderr_needed ? pipe_from_stderr : NULL),
			      toprocess_fptr, fromprocess_fptr,
			      fromproc_stderr_fptr);

    if (pid_or_status < 0) {
      xsb_warn("[%s] Subprocess creation failed", callname);
      return FALSE;
    }

    if (toproc_needed) {
      toprocess_fptr = fdopen(pipe_to_proc[1], "w");
      toproc_stream = xsb_intern_file(toprocess_fptr, callname);
      ctop_int(3, toproc_stream);
    }
    if (fromproc_needed) {
      fromprocess_fptr = fdopen(pipe_from_proc[0], "r");
      fromproc_stream = xsb_intern_file(fromprocess_fptr, callname);
      ctop_int(4, fromproc_stream);
    }
    if (fromstderr_needed) {
      fromproc_stderr_fptr = fdopen(pipe_from_stderr[0], "r");
      fromproc_stderr_stream
	= xsb_intern_file(fromproc_stderr_fptr, callname);
      ctop_int(5, fromproc_stderr_stream);
    }
    ctop_int(6, pid_or_status);

    xsb_process_table.process[tbl_pos].pid = pid_or_status;
    xsb_process_table.process[tbl_pos].to_stream = toproc_stream;
    xsb_process_table.process[tbl_pos].from_stream = fromproc_stream;
    xsb_process_table.process[tbl_pos].stderr_stream = fromproc_stderr_stream;
    concat_array(params, " ",
		 xsb_process_table.process[tbl_pos].cmdline,MAX_CMD_LEN);
    
    return TRUE;
  }

  case GET_PROCESS_TABLE: { /* sys_system(3, X). X is bound to the list
	       of the form [process(Pid,To,From,Stderr,Cmdline), ...] */
    int i;
    prolog_term table_term_tail, listHead;
    prolog_term table_term=reg_term(2);

    init_process_table();

    if (!isref(table_term))
      xsb_abort("[GET_PROCESS_TABLE] Arg 1 must be a variable");

    table_term_tail = table_term;
    for (i=0; i<MAX_SUBPROC_NUMBER; i++) {
      if (!FREE_PROC_TABLE_CELL(xsb_process_table.process[i].pid)) {
	c2p_list(table_term_tail); /* make it into a list */
	listHead = p2p_car(table_term_tail);

	c2p_functor("process", 5, listHead);
	c2p_int(xsb_process_table.process[i].pid, p2p_arg(listHead,1));
	c2p_int(xsb_process_table.process[i].to_stream, p2p_arg(listHead,2));
	c2p_int(xsb_process_table.process[i].from_stream, p2p_arg(listHead,3));
	c2p_int(xsb_process_table.process[i].stderr_stream,
		p2p_arg(listHead,4));
	c2p_string(xsb_process_table.process[i].cmdline, p2p_arg(listHead,5));

	table_term_tail = p2p_cdr(table_term_tail);
      }
    }
    c2p_nil(table_term_tail); /* bind tail to nil */
    return p2p_unify(table_term, reg_term(2));
  }

  case PROCESS_STATUS: {
    prolog_term pid_term=reg_term(2), status_term=reg_term(3);

    init_process_table();

    if (!(isinteger(pid_term)|isboxedinteger(pid_term)))
      xsb_abort("[PROCESS_STATUS] Arg 1 (process id) must be an integer");
    pid = int_val(pid_term);

    if (!isref(status_term))
      xsb_abort("[PROCESS_STATUS] Arg 2 (process status) must be a variable");
    
    switch (process_status(pid)) {
    case RUNNING:
      c2p_string("running", status_term);
      break;
    case STOPPED:
      c2p_string("stopped", status_term);
      break;
    case EXITED_NORMALLY:
      c2p_string("exited_normally", status_term);
      break;
    case EXITED_ABNORMALLY:
      c2p_string("exited_abnormally", status_term);
      break;
    case ABORTED:
      c2p_string("aborted", status_term);
      break;
    case INVALID:
      c2p_string("invalid", status_term);
      break;
    default:
      c2p_string("unknown", status_term);
    }
    return TRUE;
  }

  case PROCESS_CONTROL: {
    /* sys_system(PROCESS_CONTROL, +Pid, +Signal). Signal: wait, kill */
    int status;
    prolog_term pid_term=reg_term(2), signal_term=reg_term(3);

    init_process_table();

    if (!(isinteger(pid_term)|isboxedinteger(pid_term)))
      xsb_abort("[PROCESS_CONTROL] Arg 1 (process id) must be an integer");
    pid = int_val(pid_term);

    if (isstring(signal_term) && strcmp(string_val(signal_term), "kill")==0) {
      if (KILL_FAILED(pid))
	return FALSE;
#ifdef WIN_NT
	CloseHandle((HANDLE) pid);
#endif
      return TRUE;
    }
    if (isconstr(signal_term)
	&& strcmp(p2c_functor(signal_term),"wait") == 0
	&& p2c_arity(signal_term)==1) {
      int exit_status;

      if (WAIT(pid, status) < 0)
	return FALSE;

#ifdef WIN_NT
      exit_status = status;
#else
      if (WIFEXITED(status))
	exit_status = WEXITSTATUS(status);
      else
	exit_status = -1;
#endif

      p2p_unify(p2p_arg(signal_term,1), makeint(exit_status));
      return TRUE;
    }

    xsb_warn("[PROCESS_CONTROL] Arg 2: Invalid signal specification. Must be `kill' or `wait(Var)'");
    return FALSE;
  }
   
  case LIST_DIRECTORY: {
    /* assume all type- and mode-checking is done in Prolog */
    prolog_term handle = reg_term(2); /* ref for handle */
    char *dir_name = ptoc_longstring(3); /* +directory name */
    prolog_term filename = reg_term(4); /* reference for name of file */
    
    if (is_var(handle)) 
      return xsb_find_first_file(handle,dir_name,filename);
    else
      return xsb_find_next_file(handle,dir_name,filename);
  }

  default:
    xsb_abort("[SYS_SYSTEM] Wrong call number (an XSB bug)");
  } /* end case */
  return TRUE;
}


/* spawn a subprocess PROGNAME and pass it the arguments ARGV[]
   ARGV must be a NULL-terminated array of strings.
   Also pass it two arrays of strings: PIPE_TO_PROC[2] and PIPE_FROM_PROC[2].
   These are going to be the arrays of fds for the communication pipes 
*/
static int xsb_spawn (char *progname, char *argv[], int callno,
		      int pipe_to_proc[],
		      int pipe_from_proc[],int pipe_from_stderr[],
		      FILE *toprocess_fptr, FILE *fromprocess_fptr,
		      FILE *fromproc_stderr_fptr)
{
  int pid;
  int stdin_saved, stdout_saved, stderr_saved;
  static char shell_command[MAX_CMD_LEN];

  if ( (pipe_to_proc != NULL) && PIPE(pipe_to_proc) < 0 ) {
    /* can't open pipe to process */
    xsb_warn("[SPAWN_PROCESS] Can't open pipe for subprocess input");
    return PIPE_TO_PROC_FAILED;
  }
  if ( (pipe_from_proc != NULL) && PIPE(pipe_from_proc) < 0 ) {
    /* can't open pipe from process */
    xsb_warn("[SPAWN_PROCESS] Can't open pipe for subprocess output");
    return PIPE_FROM_PROC_FAILED;
  }
  if ( (pipe_from_stderr != NULL) && PIPE(pipe_from_stderr) < 0 ) {
    /* can't open stderr pipe from process */
    xsb_warn("[SPAWN_PROCESS] Can't open pipe for subprocess errors");
    return PIPE_FROM_PROC_FAILED;
  }

  /* The following is due to the awkwardness of windoze process creation.
     We commit this atrocity in order to be portable between Unix and Windows.
     1. Save stdio of the parent process.
     2. Redirect main process stdio to the pipes.
     3. Spawn subprocess. The subprocess inherits the redirected I/O
     4. Restore the original stdio for the parent process.

     On the bright side, this trick allowed us to cpature the I/O streams of
     the shell commands invoked by system()
  */

  /* save I/O */
  stdin_saved  = dup(fileno(stdin));
  stdout_saved = dup(fileno(stdout));
  stderr_saved = dup(fileno(stderr));
  if ((fileno(stdin) < 0) || (stdin_saved < 0))
    xsb_warn("[SPAWN_PROCESS] Bad stdin=%d; stdin closed by mistake?",
	     fileno(stdin));
  if ((fileno(stdout) < 0) || (stdout_saved < 0))
    xsb_warn("[SPAWN_PROCESS] Bad stdout=%d; stdout closed by mistake?",
	     fileno(stdout));
  if ((fileno(stderr) < 0) || (stderr_saved < 0))
    xsb_warn("[SPAWN_PROCESS] Bad stderr=%d; stderr closed by mistake?",
	     fileno(stderr));

  if (pipe_to_proc != NULL) {
    /* close child stdin, bind it to the reading part of pipe_to_proc */
    if (dup2(pipe_to_proc[0], fileno(stdin)) < 0) {
      xsb_warn("[SPAWN_PROCESS] Can't connect pipe %d to subprocess stdin",
	       pipe_to_proc[0]);
      return PIPE_TO_PROC_FAILED;
    }
    close(pipe_to_proc[0]); /* close the parent read end of pipe */
  }
  /* if stdin must be captured in an existing I/O port -- do it */
  if (toprocess_fptr != NULL)
    if (dup2(fileno(toprocess_fptr), fileno(stdin)) < 0) {
      xsb_warn("[SPAWN_PROCESS] Can't connect stream %d to subprocess stdin",
	       fileno(toprocess_fptr));
      return PIPE_TO_PROC_FAILED;
    }
  
  if (pipe_from_proc != NULL) {
    /* close child stdout, bind it to the write part of pipe_from_proc */
    if (dup2(pipe_from_proc[1], fileno(stdout)) < 0) {
      xsb_warn("[SPAWN_PROCESS] Can't connect subprocess stdout to pipe %d",
	       pipe_from_proc[1]);
      return PIPE_TO_PROC_FAILED;
    }
    close(pipe_from_proc[1]); /* close the parent write end of pipe */
  }
  /* if stdout must be captured in an existing I/O port -- do it */
  if (fromprocess_fptr != NULL)
    if (dup2(fileno(fromprocess_fptr), fileno(stdout)) < 0) {
      xsb_warn("[SPAWN_PROCESS] Can't connect subprocess stdout to stream %d",
	       fileno(fromprocess_fptr));
      return PIPE_TO_PROC_FAILED;
    }

  if (pipe_from_stderr != NULL) {
    /* close child stderr, bind it to the write part of pipe_from_proc */
    if (dup2(pipe_from_stderr[1], fileno(stderr)) < 0) {
      xsb_warn("[SPAWN_PROCESS] Can't connect subprocess stderr to pipe %d",
	       pipe_from_stderr[1]);
      return PIPE_TO_PROC_FAILED;
    }
    close(pipe_from_stderr[1]); /* close the parent write end of pipe */
  }
  /* if stderr must be captured in an existing I/O port -- do it */
  if (fromproc_stderr_fptr != NULL)
    if (dup2(fileno(fromproc_stderr_fptr), fileno(stderr)) < 0) {
      xsb_warn("[SPAWN_PROCESS] Can't connect subprocess stderr to stream %d",
	       fileno(fromproc_stderr_fptr));
      return PIPE_TO_PROC_FAILED;
    }

  if (callno == SPAWN_PROCESS) {
#ifdef WIN_NT
    pid = spawnvp(P_NOWAIT, progname, argv);
#else
    pid = fork();
#endif

    if (pid < 0) {
      /* failed */
      xsb_warn("[SPAWN_PROCESS] Can't fork off subprocess");
      return pid;
    } else if (pid == 0) {
      /* child process */

      /* Close the writing side of child's in-pipe. Must do this or else the
	 child won't see EOF when parent closes its end of this pipe. */
      if (pipe_to_proc != NULL) close(pipe_to_proc[1]);
      /* Close the reading part of child's out-pipe and stderr-pipe */
      if (pipe_from_proc != NULL) close(pipe_from_proc[0]);
      if (pipe_from_stderr != NULL) close(pipe_from_stderr[0]);
      
#ifndef WIN_NT  /* Unix: must exec */
      execvp(progname, argv);
      /* if we ever get here, this means that invocation of the process has
	 failed */
      exit(SUB_PROC_FAILED);
#endif
    }
  } else { /* SHELL command */
    /* no separator */
    concat_array(argv, "", shell_command, MAX_CMD_LEN);
    pid = system(shell_command);
  }

  /* main process continues */

  /* duplicate saved copies of stdio fds back into main process stdio */
  if (dup2(stdin_saved, fileno(stdin)) < 0) {
    perror("SPAWN_PROCESS");
    close(stdin_saved); close(stdout_saved); close(stderr_saved);
    return PIPE_TO_PROC_FAILED;
  }
  if (dup2(stdout_saved, fileno(stdout)) < 0) {
    perror("SPAWN_PROCESS");
    close(stdin_saved); close(stdout_saved); close(stderr_saved);
    return PIPE_TO_PROC_FAILED;
  }
  if (dup2(stderr_saved, fileno(stderr)) < 0) {
    perror("SPAWN_PROCESS");
    close(stdin_saved); close(stdout_saved); close(stderr_saved);
    return PIPE_TO_PROC_FAILED;
  }

  close(stdin_saved); close(stdout_saved); close(stderr_saved);
  return pid;
}

/* array is a NULL terminated array of strings. Concat it and return string */
static void concat_array(char *array[], char *separator,
			 char *result_str, int maxsize)
{
  int space_left = maxsize-1, separator_size = strlen(separator);
  char *current_pos=result_str;
  int idx=0, len;

  /* init result_str */
  *current_pos='\0';

  /* Die, he who neglects to NULL-terminate an array */
  while ((array[idx] != NULL) && (space_left > 0)) {
    len = strlen(array[idx]);

    strncat(current_pos, array[idx], space_left);
    current_pos = current_pos + (len < space_left ? len : space_left);
    *current_pos='\0';
    space_left = space_left - len;
    /* insert space separator */
    strncat(current_pos, separator, space_left);
    current_pos += separator_size;
    *current_pos='\0';
    space_left -= separator_size;
    idx++;
  }
}


static int get_free_process_cell(void) 
{
  int possible_free_cell = xsb_process_table.search_idx;
  int pid;

  do {
    pid = xsb_process_table.process[possible_free_cell].pid;
    if (FREE_PROC_TABLE_CELL(pid)) {
      /* free cell found */
      xsb_process_table.search_idx =
	(possible_free_cell + 1) % MAX_SUBPROC_NUMBER;
      return possible_free_cell;
    }
    possible_free_cell = (possible_free_cell + 1) % MAX_SUBPROC_NUMBER;
  } while (possible_free_cell != xsb_process_table.search_idx);

  /* no space */
  return -1;
}


static void init_process_table(void)
{
  static xsbBool process_table_initted = FALSE;
  int i;

  if (!process_table_initted) {
    for (i=0; i<MAX_SUBPROC_NUMBER; i++) {
      xsb_process_table.process[i].pid = -1;
    }
    xsb_process_table.search_idx = 0;
    process_table_initted = TRUE;
  }
}


/* check process status */
int process_status(int pid)
{
#ifdef WIN_NT
  long status;
  if (GetExitCodeProcess((HANDLE) pid, &status)) {
    if (status == STILL_ACTIVE)
      return RUNNING;
    else if (status == 0)
      return EXITED_NORMALLY;
    else
      return EXITED_ABNORMALLY;
  } else
    return INVALID;
#else
  int retcode;
  int status;
  /* don't wait for children that run or are stopped */
  retcode = waitpid(pid, &status, WNOHANG | WUNTRACED);

  if (retcode == 0)    	   return RUNNING; /* running	                     */
  if (retcode < 0)         return INVALID; /* doesn't exist or isn't a child */
  if (WIFSTOPPED(status))  return STOPPED; /* stopped	                     */
  if (WIFEXITED(status)) {  	    	   /* exited by an exit(code) stmt   */
    if (WEXITSTATUS(status))
      return EXITED_ABNORMALLY;
    else
      return EXITED_NORMALLY;
  }
  if (WIFSIGNALED(status)) return ABORTED; /* aborted	                     */

  return UNKNOWN; /*  unknown status */
#endif
}


/* split STRING at spaces, \t, \n, and put components
   in a NULL-terminated array.
   Take care of quoted strings and escaped symbols
   If you call it twice, the old split is forgotten.
   STRING is the string to split
   PARAMS is the array of substrings obtained as a result of the split
          these params are all sitting in a static variable, buffer.
   CALLNAME - the name of the system call. Used in error messages.
*/
static void split_command_arguments(char *string, char *params[], char *callname)
{
  int buflen = strlen(string);
  int idx = 0;
  char *buf_ptr, *arg_ptr;
  static char buffer[MAX_CMD_LEN];

  if (buflen > MAX_CMD_LEN - 1)
    xsb_abort("[%s] Command string too long", callname);

  buf_ptr = buffer;

  /* Debugging
  fprintf(stderr,"%s\n", string);
  */
  do {
    arg_ptr = get_next_command_argument(&buf_ptr,&string);
    params[idx] = arg_ptr;
    /* Debugging
    fprintf(stderr,"%s\n", arg_ptr);
    */
    idx++;
  } while (arg_ptr != NULL && idx <= MAX_SUBPROC_PARAMS);
  /* note: params has extra space, so not to worry about <= */

  return;
}


/*
  Copies next command argument from CMD_LINE to the next free place in buffer
  and returns the pointer to the null-terminated string that represents that
  argument. Advances the pointers into the CMD_LINE and BUFFER so that the
  caller can use them to call get_next_command_argument again.
*/
static char *get_next_command_argument(char **buffptr, char **cmdlineprt)
{
  short escaped=FALSE;
  char quoted = '\0';
  char *returnptr = *buffptr;

  /* skip white space */
  while (isspace(**cmdlineprt))
    (*cmdlineprt)++;

  /* loop as long as not end of cmd line or until the next command argument has
     been found and extracted */
  while ((!isspace(**cmdlineprt) || quoted) && **cmdlineprt != '\0') {
    if (escaped) {
      switch (**cmdlineprt) {
      case 'b': **buffptr='\b'; break;
      case 'f': **buffptr='\f'; break;
      case 'n': **buffptr='\n'; break;
      case 'r': **buffptr='\r'; break;
      case 't': **buffptr='\t'; break;
      case 'v': **buffptr='\v'; break;
      default:
	**buffptr=**cmdlineprt;
      }
      (*buffptr)++;
      (*cmdlineprt)++;
      escaped=FALSE;
      continue;
    }
    switch (**cmdlineprt) {
    case '"':
    case '\'':
      if (!quoted) {
	/* begin quoted string */
	quoted = **cmdlineprt;
      } else if (quoted == **cmdlineprt) {
	/* end the quoted part of the argument */
	quoted = '\0';
      } else {
	/* quote symbol inside string quoted by a different symbol */
	**buffptr=**cmdlineprt;
	(*buffptr)++;
      }
      (*cmdlineprt)++;
      break;
#ifndef WIN_NT
    case '\\':
      escaped = TRUE;
      (*cmdlineprt)++;
      break;
#endif
    default:
      **buffptr=**cmdlineprt;
      (*buffptr)++;
      (*cmdlineprt)++;
    }
  }

  if (returnptr==*buffptr)
    return NULL;

  **buffptr='\0';
  (*buffptr)++;
  return returnptr;
}



/* use stat() to get file mod time, size, and other things */
/* file_stat(+FileName, +FuncNumber, -Result)	     	   */
xsbBool file_stat(int callno, char *file)
{
  struct stat stat_buff;
  int retcode = stat(file, &stat_buff);

  switch (callno) {
  case IS_PLAIN_FILE: {
    if (retcode == 0 && S_ISREG(stat_buff.st_mode)) 
      return TRUE;
    else return FALSE;
  }
  case IS_DIRECTORY: {
    if (retcode == 0 && S_ISDIR(stat_buff.st_mode)) 
      return TRUE;
    else return FALSE;
  }
  case STAT_FILE_TIME: {
    /* This is DSW's hack to get 32 bit time values.
       The idea is to call this builtin as file_time(File,time(T1,T2))
       where T1 represents the most significant 8 bits and T2 represents
       the least significant 24.
       ***This probably breaks 64 bit systems, so David will look into it!
       */
    int functor_arg3 = isconstr(reg_term(3));
    if (!retcode && functor_arg3) {
      /* file exists & arg3 is a term, return 2 words*/
      c2p_int(stat_buff.st_mtime >> 24,p2p_arg(reg_term(3),1));
      c2p_int(0xFFFFFF & stat_buff.st_mtime,p2p_arg(reg_term(3),2));
    } else if (!retcode) {
      /* file exists, arg3 non-functor:  issue an error */
      xsb_warn("Arg 3 (the time argument) must be of the form time(X,Y)");
      ctop_int(3, (0x7FFFFFF & stat_buff.st_mtime));
    } else if (functor_arg3) {
      /* no file, and arg3 is functor: return two 0's */
      c2p_int(0, p2p_arg(reg_term(3),2));
      c2p_int(0, p2p_arg(reg_term(3),1));
    } else {
      /* no file, no functor: return 0 */
      xsb_warn("Arg 3 (the time argument) must be of the form time(X,Y)");
      ctop_int(3, 0);
    }
    return TRUE;
  }
  case STAT_FILE_SIZE: { /* Return size in bytes. */
    /*** NOTE: Same hack as with time. However, return a list
	 because the path_sysop() interface in file_io returns lists
	 both for time and size. */
    prolog_term size_lst = p2p_new();
    prolog_term elt1, elt2, tail;
    if (!retcode) {
      /* file exists */
      c2p_list(size_lst);
      elt1 = p2p_car(size_lst);
      tail = p2p_cdr(size_lst);
      c2p_list(tail);
      elt2 = p2p_car(tail);
      tail = p2p_cdr(tail); c2p_nil(tail);
      c2p_int(stat_buff.st_size >> 24, elt1);
      c2p_int(0xFFFFFF & stat_buff.st_size, elt2);
      p2p_unify(size_lst,reg_term(3));
      return TRUE;
    } else  /* no file */
      return FALSE;
  }
  default:
    xsb_abort("Unsupported file_stat code: %d\n", callno);
    return FALSE;
  } /* switch */
}

static int xsb_find_first_file(prolog_term handle,
			       char *dir,
			       prolog_term file)
{
#ifdef WIN_NT
  WIN32_FIND_DATA filedata;
  HANDLE filehandle;

  filehandle = FindFirstFile(dir,&filedata);
  if (filehandle == INVALID_HANDLE_VALUE)
    return FALSE;
  c2p_int((Integer)filehandle,handle);
  c2p_string(filedata.cFileName,file);
  return TRUE;
#else
  DIR *dirhandle;
  struct dirent *dir_entry;
  
  dirhandle = opendir(dir);
  if (!dirhandle)
    return FALSE;
  dir_entry = readdir(dirhandle);
  if (!dir_entry) {
    closedir(dirhandle);
    return FALSE;
  }
  c2p_int((Integer)dirhandle,handle);
  c2p_string(dir_entry->d_name,file);
  return TRUE;
#endif
}

static int xsb_find_next_file(prolog_term handle,
			      char *dir,
			      prolog_term file)
{
#ifdef WIN_NT
  WIN32_FIND_DATA filedata;
  HANDLE filehandle;
  
  filehandle = p2c_int(handle);
  if (!FindNextFile(filehandle,&filedata)) 
    return FALSE;
  c2p_string(filedata.cFileName,file);
  return TRUE;
#else
  DIR *dirhandle = (DIR *) p2c_int(handle);
  struct dirent *dir_entry;

  dir_entry = readdir(dirhandle);
  if (!dir_entry) {
    closedir(dirhandle);
    return FALSE;
  }
  c2p_string(dir_entry->d_name,file);
  return TRUE;
#endif
}