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
#ifndef HPL_LOWLEVELINPUT_H
#define HPL_LOWLEVELINPUT_H

namespace hpl {

	class iMouse;
	class iKeyboard;
	class iInputDevice;

	class iLowLevelInput
	{
	public:
		// Typedefs -- Ricky26
		typedef unsigned int tCount;

		virtual ~iLowLevelInput(){}
		
		/**
		 * Lock all input to current window.
		 * \param abX 
		 * \return 
		 */
		virtual void LockInput(bool abX)=0;
		/**
		 * Called by cInput
		 */
		virtual void BeginInputUpdate()=0;
		/**
		 * called by cInput
		 */
		virtual void EndInputUpdate()=0;

		// Renamed to make more sense -- Ricky26
		virtual iMouse* GetMouse()=0;
		virtual iKeyboard* GetKeyboard()=0;
		
		// More input devices! -- Ricky26
		virtual tCount DeviceCount()=0;
		virtual iInputDevice *GetDevice(tCount)=0;
	};
};
#endif // HPL_LOWLEVELINPUT_H
