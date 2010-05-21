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
#include "input/InputDevice.h"
#include "input/InputControl.h"

namespace hpl
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	iInputDevice::iInputDevice(tString asName): msName(asName)
	{

	}
	
	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////
	
	//-----------------------------------------------------------------------
	
	tString iInputDevice::GetName(){
		return msName;
	}

	//-----------------------------------------------------------------------

	bool iInputDevice::IsActive()
	{
		size_t count = ChildCount();
		for(size_t i = 0; i < count; i++)
		{
			if(GetChild(i)->IsTriggered())
				return true;
		}

		return false;
	}

	bool iInputDevice::AssignControl(cAction *_action)
	{
		return false;
	}
	
	iInputControl *iInputDevice::FindControl(tString _name)
	{
		size_t count = ChildCount();
		for(size_t i = 0; i < count; i++)
		{
			iInputControl *chld = GetChild(i);
			if(chld && chld->GetName().compare(_name) == 0)
				return chld;
		}
		
		return NULL;
	}
}
