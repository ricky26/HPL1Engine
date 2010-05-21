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

#include "input/InputControl.h"

namespace hpl
{
	iInputControl::iInputControl(iInputDevice *_dev)
	{
		mpDevice = _dev;
	}

	iInputDevice *iInputControl::GetDevice()
	{
		return mpDevice;
	}

	size_t iInputControl::ChildCount()
	{
		return 0;
	}

	iInputControl *iInputControl::GetChild(size_t _idx)
	{
		return NULL;
	}

	bool iInputControl::AddAction(cAction *_act)
	{
		for(tActionList::iterator i = mActions.begin(); i != mActions.end(); i++)
		{
			if(*i == _act)
				return false;
		}

		if(!_act->AddControl(this))
			return false;

		mActions.push_back(_act);
		return true;
	}

	void iInputControl::RemoveAction(cAction *_act)
	{
		for(tActionList::iterator i = mActions.begin(); i != mActions.end(); i++)
		{
			if(*i == _act)
			{
				mActions.erase(i);
				return;
			}
		}
	}

	size_t iInputControl::ActionCount()
	{
		return mActions.size();
	}

	cAction *iInputControl::GetAction(size_t _idx)
	{
		return mActions[_idx];
	}

	void iInputControl::Trigger(bool _on)
	{
		for(tActionList::iterator i = mActions.begin(); i != mActions.end(); i++)
		{
			(*i)->Triggered(_on);
		}
	}
};
