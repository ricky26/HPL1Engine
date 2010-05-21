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
#ifndef HPL_INPUT_H
#define HPL_INPUT_H

#include <map>
#include <vector>

#include "system/SystemTypes.h"
#include "game/Updateable.h"
#include "input/InputTypes.h"
#include "input/Action.h"

namespace hpl {

	class iKeyboard;
	class iMouse;
	class iLowLevelInput;
	class iInputDevice;

	typedef std::vector<iInputDevice*> tInputDeviceList;
	typedef tInputDeviceList::iterator tInputDeviceListIt;

	class cInput : public iUpdateable
	{
	public:
		cInput(iLowLevelInput *apLowLevelInput);
        ~cInput();
		
		/**
		 * Updates the input, called by cGame
		 */
		void Update(float afTimeStep);
		
		/**
		 *
		 * \return currently used keyboard
		 */
		iKeyboard *GetKeyboard();

		/**
		*
		* \return currently used mouse
		*/
		iMouse *GetMouse();

		/**
		 * \return the device by that name, or NULL if not found.
		 */
		iInputDevice *FindDevice(tString _name);

		/**
		 * \return the group that contains all configurable actions.
		 */
		cActionGroup *GetActionGroup();

		/**
		 * Checks if any input is given.
		 * \return true if any input is given, else false.
		 */
		bool CheckForInput();

		/**
		 * Attempt to assign a currently active control to
		 * the supplied action.
		 */
		bool AssignControl(cAction *);

		/**
		 * Load an input configuration from a file.
		 * \returns whether the operation was a success.
		 */
		bool LoadLayout(tWString _path);

		/**
		 * Save an input configuration to a file.
		 * \returns whether the operation was a success.
		 */
		bool SaveLayout(tWString _path);

		iLowLevelInput* GetLowLevel(){ return mpLowLevelInput;}

	private:
		tInputDeviceList mlstInputDevices;
		cActionGroup mRootActionGroup;

		iLowLevelInput *mpLowLevelInput;
		
		iMouse* mpMouse;
		iKeyboard* mpKeyboard;
	};
};

#endif // HPL_INPUT_H
