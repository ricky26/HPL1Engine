/*
 * Copyright (C) 2006-2010 - Frictional Games
 *
 * This file is part of HPL1 Engine.
 *
 * HPL1 Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HPL1 Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HPL1 Engine.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "input/Keyboard.h"

namespace hpl
{
	cKeyboardButton::cKeyboardButton(iKeyboard *_kb, eKey _btn): iInputControl(_kb)
	{
		mpParent = _kb;
		mKey = _btn;
		mName = iKeyboard::KeyName(_btn);
	}

	tString cKeyboardButton::GetName()
	{
		return mName;
	}

	bool cKeyboardButton::IsTriggered()
	{
		return mpParent->KeyIsDown(mKey);
	}
	
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	iKeyboard::iKeyboard(tString asName) : iInputDevice(asName)
	{
		mButtons.reserve(eKey_NONE);
		for(int i = 0; i < eKey_NONE; i++)
		{
			cKeyboardButton *btn = new cKeyboardButton(this, (eKey)i);
			mButtons.push_back(btn);
		}
	}
	
	//-----------------------------------------------------------------------

	iKeyboard::~iKeyboard()
	{
		for(tKeyboardButtonList::iterator i = mButtons.begin(); i != mButtons.end(); i++)
		{
			delete *i;
		}
		mButtons.clear();
	}

	//-----------------------------------------------------------------------

	cKeyboardButton *iKeyboard::GetButton(eKey key)
	{
		if(key >= 0 && key < eKey_NONE)
		{
			return mButtons[key];
		}

		return NULL;
	}

	//-----------------------------------------------------------------------

	void iKeyboard::TriggerKey(eKey _key, bool _val)
	{
		cKeyboardButton *btn = GetButton(_key);
		if(btn)
		{
			btn->Trigger(_val);
		}
	}
	
	//-----------------------------------------------------------------------

	size_t iKeyboard::ChildCount()
	{
		return mButtons.size();
	}

	//-----------------------------------------------------------------------

	iInputControl *iKeyboard::GetChild(size_t _idx)
	{
		return mButtons[_idx];
	}
	
	//

	tString iKeyboard::KeyName(eKey _key)
	{
		switch(_key)
		{
			case eKey_BACKSPACE: return ("BackSpace"); break;
			case eKey_TAB: return ("Tab"); break;
			case eKey_CLEAR: return ("Clear"); break;
			case eKey_RETURN: return ("Return"); break;
			case eKey_PAUSE: return ("Pause"); break;
			case eKey_ESCAPE: return ("Escape"); break;
			case eKey_SPACE: return ("Space"); break;
			case eKey_EXCLAIM: return ("Exclaim"); break;
			case eKey_QUOTEDBL: return ("DblQoute"); break;
			case eKey_HASH: return ("Hash"); break;
			case eKey_DOLLAR: return ("Dollar"); break;
			case eKey_AMPERSAND: return ("Ampersand"); break;
			case eKey_QUOTE: return ("Quote"); break;
			case eKey_LEFTPAREN: return ("LeftParent"); break;
			case eKey_RIGHTPAREN: return ("RightParent"); break;
			case eKey_ASTERISK: return ("Asterisk"); break;
			case eKey_PLUS: return ("Plus"); break;
			case eKey_COMMA: return ("Comma"); break;
			case eKey_MINUS: return ("Minus"); break;
			case eKey_PERIOD: return ("Period"); break;
			case eKey_SLASH: return ("Slash"); break;
			case eKey_0: return ("0"); break;
			case eKey_1: return ("1"); break;
			case eKey_2: return ("2"); break;
			case eKey_3: return ("3"); break;
			case eKey_4: return ("4"); break;
			case eKey_5: return ("5"); break;
			case eKey_6: return ("6"); break;
			case eKey_7: return ("7"); break;
			case eKey_8: return ("8"); break;
			case eKey_9: return ("9"); break;
			case eKey_COLON: return ("Colon"); break;
			case eKey_SEMICOLON: return ("SemiColon"); break;
			case eKey_LESS: return ("Less"); break;
			case eKey_EQUALS: return ("Equals"); break;
			case eKey_GREATER: return ("Greater"); break;
			case eKey_QUESTION: return ("Question"); break;
			case eKey_AT: return ("At"); break;
			case eKey_LEFTBRACKET: return ("LeftBracket"); break;
			case eKey_BACKSLASH: return ("BackSlash"); break;
			case eKey_RIGHTBRACKET: return ("RightBracket"); break;
			case eKey_CARET: return ("Caret"); break;
			case eKey_UNDERSCORE: return ("Underscore"); break;
			case eKey_BACKQUOTE: return ("BackQuote"); break;
			case eKey_a: return ("A"); break;
			case eKey_b: return ("B"); break;
			case eKey_c: return ("C"); break;
			case eKey_d: return ("D"); break;
			case eKey_e: return ("E"); break;
			case eKey_f: return ("F"); break;
			case eKey_g: return ("G"); break;
			case eKey_h: return ("H"); break;
			case eKey_i: return ("I"); break;
			case eKey_j: return ("J"); break;
			case eKey_k: return ("K"); break;
			case eKey_l: return ("L"); break;
			case eKey_m: return ("M"); break;
			case eKey_n: return ("N"); break;
			case eKey_o: return ("O"); break;
			case eKey_p: return ("P"); break;
			case eKey_q: return ("Q"); break;
			case eKey_r: return ("R"); break;
			case eKey_s: return ("S"); break;
			case eKey_t: return ("T"); break;
			case eKey_u: return ("U"); break;
			case eKey_v: return ("V"); break;
			case eKey_w: return ("W"); break;
			case eKey_x: return ("X"); break;
			case eKey_y: return ("Y"); break;
			case eKey_z: return ("Z"); break;
			case eKey_DELETE: return ("Delete"); break;
			case eKey_KP0: return ("Kp0"); break;
			case eKey_KP1: return ("Kp1"); break;
			case eKey_KP2: return ("Kp2"); break;
			case eKey_KP3: return ("Kp3"); break;
			case eKey_KP4: return ("Kp4"); break;
			case eKey_KP5: return ("Kp5"); break;
			case eKey_KP6: return ("Kp6"); break;
			case eKey_KP7: return ("Kp7"); break;
			case eKey_KP8: return ("Kp8"); break;
			case eKey_KP9: return ("Kp9"); break;
			case eKey_KP_PERIOD: return ("Period"); break;
			case eKey_KP_DIVIDE: return ("Divide"); break;
			case eKey_KP_MULTIPLY: return ("Multiply"); break;
			case eKey_KP_MINUS: return ("Minus"); break;
			case eKey_KP_PLUS: return ("Plus"); break;
			case eKey_KP_ENTER: return ("Enter"); break;
			case eKey_KP_EQUALS: return ("Equals"); break;
			case eKey_UP: return ("Up"); break;
			case eKey_DOWN: return ("Down"); break;
			case eKey_RIGHT: return ("Right"); break;
			case eKey_LEFT: return ("Left"); break;
			case eKey_INSERT: return ("Insert"); break;
			case eKey_HOME: return ("Home"); break;
			case eKey_END: return ("End"); break;
			case eKey_PAGEUP: return ("PageUp"); break;
			case eKey_PAGEDOWN: return ("PageDown"); break;
			case eKey_F1: return ("F1"); break;
			case eKey_F2: return ("F2"); break;
			case eKey_F3: return ("F3"); break;
			case eKey_F4: return ("F4"); break;
			case eKey_F5: return ("F5"); break;
			case eKey_F6: return ("F6"); break;
			case eKey_F7: return ("F7"); break;
			case eKey_F8: return ("F8"); break;
			case eKey_F9: return ("F9"); break;
			case eKey_F10: return ("F10"); break;
			case eKey_F11: return ("F11"); break;
			case eKey_F12: return ("F12"); break;
			case eKey_F13: return ("F13"); break;
			case eKey_F14: return ("F14"); break;
			case eKey_F15: return ("F15"); break;
			case eKey_NUMLOCK: return ("NumLock"); break;
			case eKey_CAPSLOCK: return ("CapsLock"); break;
			case eKey_SCROLLOCK: return ("ScrollLock"); break;
			case eKey_RSHIFT: return ("RightShift"); break;
			case eKey_LSHIFT: return ("LeftShift"); break;
			case eKey_RCTRL: return ("RightControl"); break;
			case eKey_LCTRL: return ("LeftControl"); break;
			case eKey_RALT: return ("RightAlt"); break;
			case eKey_LALT: return ("LeftAlt"); break;
			case eKey_RMETA: return ("RightMeta"); break;
			case eKey_LMETA: return ("LeftMeta"); break;
			case eKey_LSUPER: return ("LeftSuper"); break;
			case eKey_RSUPER: return ("RightSuper"); break;
			case eKey_MODE: return ("Mode"); break;
			case eKey_HELP: return ("Help"); break;
			case eKey_PRINT: return ("Print"); break;
			case eKey_SYSREQ: return ("SysReq"); break;
			case eKey_BREAK: return ("Break"); break;
			case eKey_MENU: return ("Menu"); break;
			case eKey_POWER: return ("Power"); break;
			case eKey_EURO: return ("Euro"); break;
			case eKey_NONE: return ("None"); break;
		}

		return "Button";
	}
}
