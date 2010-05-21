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

#include "input/Mouse.h"
#include <sstream>

namespace hpl
{
	cMouseMovement::cMouseMovement(iMouse *_ms, MouseAxis _axis): iInputMovement(_ms)
	{
		mpParent = _ms;
		mAxis = _axis;
		mName = _axis == XAxis ? "XAxis" : "YAxis";
		mfDistance = 0;
	}

	tString cMouseMovement::GetName()
	{
		return mName;
	}

	float cMouseMovement::TriggeredDistance()
	{
		return mfDistance;
	}

	void cMouseMovement::ResetDistance()
	{
		mfDistance = 0;
	}

	void cMouseMovement::TriggerDistance(float _mv)
	{
		mfDistance += _mv;
		iInputMovement::TriggerDistance(_mv);
	}

	cMouseButton::cMouseButton(iMouse *_ms, int _btn): iInputControl(_ms)
	{
		mpParent = _ms;
		mBtn = _btn;

		std::stringstream name;
		name << (_btn+1);
		mName = name.str();
	}

	tString cMouseButton::GetName()
	{
		return mName;
	}

	bool cMouseButton::IsTriggered()
	{
		return mpParent->ButtonIsDown(mBtn);
	}

	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	iMouse::iMouse(tString asName) : iInputDevice(asName),
		mXAxis(this, cMouseMovement::XAxis),
		mYAxis(this, cMouseMovement::YAxis)
	{
		mButtons.reserve(mouseButtonCount);
		for(int i = 0; i < mouseButtonCount; i++)
		{
			cMouseButton *btn = new cMouseButton(this, i);
			mButtons.push_back(btn);
		}
	}

	//-----------------------------------------------------------------------

	iMouse::~iMouse()
	{
		for(tMouseButtonList::iterator i = mButtons.begin(); i != mButtons.end(); i++)
		{
			delete *i;
		}
		mButtons.clear();
	}

	//-----------------------------------------------------------------------

	void iMouse::TriggerButton(int _btn, bool _val)
	{
		cMouseButton *btn = mButtons[_btn];
		if(btn)
		{
			btn->Trigger(_val);
		}
	}
	
	//-----------------------------------------------------------------------

	size_t iMouse::ChildCount()
	{
		return mButtons.size() + 2;
	}

	//-----------------------------------------------------------------------

	iInputControl *iMouse::GetChild(size_t _idx)
	{
		if(_idx == 0)
			return &mXAxis;

		if(_idx == 1)
			return &mYAxis;

		return mButtons[_idx-2];
	}
}
