/*
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and
 * limitations under the License.
 *
 * The Original Code is Navajo Verb Morphology Parser code.
 *
 * The Initial Developer of the Original Code is
 * Eden Siu-yue Li.
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 */

var BARRED_L    = String.fromCharCode(0x026b);
var ACCENT_MARK = String.fromCharCode(0x0301);
var UNDER_HOOK  = String.fromCharCode(0x0345);

function handleKeyPress (e) {
    if (e.altKey && e.charCode != 0) {
        switch (e.charCode) {
            case 49: // '1'
                addChar (BARRED_L);
                break;
            case 50: // '2'
                addChar (ACCENT_MARK);
                break;
            case 51: // '3'
                addChar (UNDER_HOOK);
                break;
        }
    }
}

function addChar (cl) {
    if (document.getElementById) {
        var inp = document.getElementById("input");
        var inpValue = inp.value;

        // check all the diacritic marks to see if cl
        // was already added
        if (isDiacritic (cl, 0)) {
            var i = inpValue.length-1;
            var okToPlace = true;
            while (i >= 0 && isDiacritic (inpValue, i)) {
                if (inpValue.charAt (i) == cl) {
                    okToPlace = false;
                    break;
                }
                i--;
            }

            // only add to vowels a, e, i, o
            if (!isVowel (inpValue, i))
                okToPlace = false;

            // if the char to add is a high tone and the
            // previous char is a nasal, don't add
            if (cl.charCodeAt(0) == 0x301 &&
                    inpValue.charCodeAt (inpValue.length-1) == 0x345)
                okToPlace = false;

            if (okToPlace) {
                inp.value += cl;
            }
        }
        else {
            inp.value += cl;
        }
        inp.focus ();
        
        return true;
    }
    return false;
}

function isVowel (c, index) {
    switch (c.charAt (index)) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
            return true;
    }
    return false;
}

function isDiacritic (c, index) {
    return c.charCodeAt (index) >= 0x300 &&
        c.charCodeAt (index) <= 0x36F;
}

function addEvent(obj, evType, fn){ 
    if (obj.addEventListener){ 
        obj.addEventListener (evType, fn, true); 
        return true; 
    } else if (obj.attachEvent){ 
        var r = obj.attachEvent ("on" + evType, fn); 
        return r; 
    } else { 
        return false; 
    } 
}

function collapseExpand () {
    if (document.getElementById) {
        for (var i = 0; i < collapseExpand.arguments.length; i++) {
            var element = document.getElementById (collapseExpand.
                                                   arguments[i]);
            element.style.display =
                (element.style.display == 'none' ?
                    'block' :
                    'none');
        }
    }
}

function onLoad (ev) {
    /*document.getElementById('help').style.display = 'block';
    document.getElementById('helphidden').style.display = 'none';*/

    if (document.getElementById) {
        if (document.getElementById('underlying')) {
            document.getElementById('underlying').style.display = 'none';
        }

        var input = document.getElementById ('input');
        if (input) {
            addEvent (input, "keypress", handleKeyPress);
            input.focus();
        }
    }
}

addEvent (window, 'load', onLoad);
