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

#include "input/InputHat.h"

namespace hpl
{
	/////
	// cInputHatAxis implementation.
	/////

	cInputHatAxis::cInputHatAxis(iInputHat *_parent, HatAxis _axis): iInputAxis(_parent->GetDevice())
	{
		mpParent = _parent;
		mAxis = _axis;
		mName = "";
	}

	tString cInputHatAxis::GetName()
	{
		if(mName.length() == 0)
		{
			mName = mpParent->GetName();
			switch(mAxis)
			{
			case TopBottom:
				mName += " YAxis";
				break;

			case LeftRight:
				mName += " XAxis";
				break;

			case TopLeftBottomRight:
				mName += " -Diagonal";
				break;

			case TopRightBottomLeft:
				mName += " +Diagonal";
				break;
			}
		}

		return mName;
	}

	float cInputHatAxis::TriggeredAmount()
	{
		iInputHat::HatDirection dir = mpParent->TriggeredDirection();
		if(dir == iInputHat::Middle)
			return 0;
		
		switch(mAxis)
		{
		case TopBottom:
			{
				if(dir == iInputHat::Bottom)
					return 1;

				return -1;
			}

		case LeftRight:
			{
				if(dir == iInputHat::Right)
					return 1;

				return -1;
			}

		case TopLeftBottomRight:
			{
				if(dir == iInputHat::BottomRight)
					return 1;

				return -1;
			}

		case TopRightBottomLeft:
			{
				if(dir == iInputHat::TopRight)
					return 1;

				return -1;
			}

		default:
			return 0;
		}
	}

	iInputHat::iInputHat(iInputDevice *_dev)
		: iInputControl(_dev)
	{
		mAxisTB = new cInputHatAxis(this, cInputHatAxis::TopBottom);
		mAxisLR = new cInputHatAxis(this, cInputHatAxis::LeftRight);
		mAxisTLBR = new cInputHatAxis(this, cInputHatAxis::TopLeftBottomRight);
		mAxisTRBL = new cInputHatAxis(this, cInputHatAxis::TopRightBottomLeft);
	}
	
	iInputHat::~iInputHat()
	{
		delete mAxisTB;
		delete mAxisLR;
		delete mAxisTLBR;
		delete mAxisTRBL;
	}

	size_t iInputHat::ChildCount()
	{
		size_t count = 4;
		count += mAxisTB->ChildCount() * 4;
		return count;
	}

	iInputControl *iInputHat::GetChild(size_t _idx)
	{
		switch(_idx)
		{
		case 0:
			return mAxisTB;
		case 1:
			return mAxisLR;
		case 2:
			return mAxisTLBR;
		case 3:
			return mAxisTRBL;
		}
		_idx -= 4;

		size_t count = mAxisTB->ChildCount();
		if(_idx < count)
			return mAxisTB->GetChild(_idx);
		_idx -= count;

		count = mAxisLR->ChildCount();
		if(_idx < count)
			return mAxisLR->GetChild(_idx);
		_idx -= count;

		count = mAxisTLBR->ChildCount();
		if(_idx < count)
			return mAxisTLBR->GetChild(_idx);
		_idx -= count;

		count = mAxisTRBL->ChildCount();
		if(_idx < count)
			return mAxisTRBL->GetChild(_idx);
		_idx -= count;

		return NULL;
	}

	bool iInputHat::IsTriggered()
	{
		return TriggeredDirection() != Middle;
	}

	void iInputHat::TriggerDirection(HatDirection _dir)
	{
		if(_dir != TriggeredDirection())
		{
			switch(TriggeredDirection())
			{
			case Top:
			case Bottom:
				mAxisTB->TriggerAmount(0);
				break;

			case Left:
			case Right:
				mAxisLR->TriggerAmount(0);
				break;

			case TopLeft:
			case BottomRight:
				mAxisTLBR->TriggerAmount(0);
				break;

			case TopRight:
			case BottomLeft:
				mAxisTRBL->TriggerAmount(0);
				break;
			}

			switch(_dir)
			{
			case Top:
				mAxisTB->TriggerAmount(-1);
				break;

			case Bottom:
				mAxisTB->TriggerAmount(1);
				break;

			case Left:
				mAxisLR->TriggerAmount(-1);
				break;

			case Right:
				mAxisLR->TriggerAmount(1);
				break;

			case TopLeft:
				mAxisTLBR->TriggerAmount(-1);
				break;

			case BottomRight:
				mAxisTLBR->TriggerAmount(1);
				break;

			case BottomLeft:
				mAxisTRBL->TriggerAmount(-1);
				break;

			case TopRight:
				mAxisTRBL->TriggerAmount(1);
				break;
			}
		}

		// TODO: Implement hat actions! -- Ricky26
	}
};
