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
#ifndef HPL_KEYBOARD_H
#define HPL_KEYBOARD_H

#include "input/InputTypes.h"
#include "input/InputDevice.h"
#include "input/InputControl.h"

namespace hpl {

	class iKeyboard;
	class cKeyboardButton: public iInputControl
	{
	public:
		friend class iKeyboard;

		cKeyboardButton(iKeyboard *_ms, eKey _btn);

		virtual tString GetName();
		virtual bool IsTriggered();

	protected:
		tString mName;
		iKeyboard *mpParent;
		eKey mKey;
	};

	// TODO: Fix modifiers! -- Ricky26
	class iKeyboard : public iInputDevice
	{
	public:
		typedef std::vector<cKeyboardButton*> tKeyboardButtonList;

		iKeyboard(tString asName);
		virtual ~iKeyboard();
		
		/**
		 * 
		 * \param aKey The key to check 
		 * \return true if pressed else false 
		 */
		virtual bool KeyIsDown(eKey aKey)=0;

		/**
		 * Can be checked many times to see all key presses
		 * \return key that is currently pressed. eKey_NONE is no key. 
		 */
		virtual cKeyPress GetKey()=0;

		/**
		 *
		 * \return If ANY key is pressed
		 */
		virtual bool KeyIsPressed()=0;

		/**
		 * \return The current modifiers.
		 */
		virtual eKeyModifier GetModifier()=0;

		/**
		 * \param eKey The eKey who's name we want.
		 * \return The name of the eKey.
		 */
		static tString KeyName(eKey);

		virtual size_t ChildCount();
		virtual iInputControl *GetChild(size_t);
		
		cKeyboardButton *GetButton(eKey key);

	protected:
		void TriggerKey(eKey _key, bool _val);


		tKeyboardButtonList mButtons;
	};

};

#endif // HPL_KEYBOARD_H
