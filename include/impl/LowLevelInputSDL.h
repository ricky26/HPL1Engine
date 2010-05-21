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
#ifndef HPL_LOWLEVELINPUT_SDL_H
#define HPL_LOWLEVELINPUT_SDL_H

#include <list>
#include <vector>
#include "input/LowLevelInput.h"

#include "SDL/SDL.h"

namespace hpl {

	class iLowLevelGraphics;

	class cLowLevelInputSDL : public iLowLevelInput
	{
	public:
		typedef std::list<SDL_Event> tEventList;
		typedef std::vector<iInputDevice*> tDeviceList;

		static const int defaultDeviceCapacity = 16; // This means 14 'other' devices. (eg: joysticks) -- Ricky26

		cLowLevelInputSDL(iLowLevelGraphics *apLowLevelGraphics);
		~cLowLevelInputSDL();

		void LockInput(bool abX);

		void BeginInputUpdate();
		void EndInputUpdate();

		iMouse* GetMouse();
		iKeyboard* GetKeyboard();

		// More input devices! -- Ricky26
		tCount DeviceCount();
		iInputDevice *GetDevice(tCount);

	public:
		tEventList mlstEvents;

	private: 
		iLowLevelGraphics *mpLowLevelGraphics;
		iMouse *mpMouse;
		iKeyboard *mpKeyboard;
		tDeviceList mDevices;
		
	};
};
#endif // HPL_LOWLEVELINPUT_SDL_H
