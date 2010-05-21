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

#include "input/InputAxis.h"
#include "input/AxisAction.h"

namespace hpl
{
	//////
	// cInputAxisControl Implementation
	//////

	cInputAxisControl::cInputAxisControl(iInputAxis *_parent, AxisControl _axis): iInputControl(_parent->GetDevice())
	{
		mpParent = _parent;
		mAxis = _axis;
		mName = "";
	}

	tString cInputAxisControl::GetName()
	{
		if(mName.length() == 0)
		{
			mName = mpParent->GetName() + (mAxis == Positive ? "+" : "-");
		}

		return mName;
	}

	bool cInputAxisControl::IsTriggered()
	{
		return (mAxis == Positive && mpParent->TriggeredAmount() > mpParent->GetThreshold())
			|| (mAxis == Negative && mpParent->TriggeredAmount() < -mpParent->GetThreshold());
	}

	//////
	// iInputAxis Implementation
	//////

	iInputAxis::iInputAxis(iInputDevice *_dev)
		: iInputControl(_dev)
	{
		mControlPositive = new cInputAxisControl(this, cInputAxisControl::Positive);
		mControlNegative = new cInputAxisControl(this, cInputAxisControl::Negative);

		mfOffset = 0;
		mfDeadZone = 0;
		mfCutoff = 1;
		mfRange = 1;
		mfScale = 1;
		mfFunction = 1;
	}

	iInputAxis::~iInputAxis()
	{
		delete mControlPositive;
		delete mControlNegative;
	}

	void iInputAxis::SetFunction(float _fnc)
	{
		mfFunction = _fnc;
	}

	float iInputAxis::GetFunction()
	{
		return mfFunction;
	}
	
	void iInputAxis::SetOffset(float _amt)
	{
		mfOffset = _amt;
	}

	float iInputAxis::GetOffset()
	{
		return mfOffset;
	}

	void iInputAxis::SetDeadZone(float _amt)
	{
		mfDeadZone = _amt;
		mfRange = mfCutoff-mfDeadZone;
	}

	float iInputAxis::GetDeadZone()
	{
		return mfDeadZone;
	}

	void iInputAxis::SetCutoff(float _amt)
	{
		mfCutoff = _amt;
		mfRange = mfCutoff-mfDeadZone;
	}

	float iInputAxis::GetCutoff()
	{
		return mfCutoff;
	}

	float iInputAxis::GetRange()
	{
		return mfRange;
	}
	
	void iInputAxis::SetScale(float _amt)
	{
		mfScale = _amt;
	}

	float iInputAxis::GetScale()
	{
		return mfScale;
	}

	size_t iInputAxis::ChildCount()
	{
		return 2;
	}

	iInputControl *iInputAxis::GetChild(size_t _idx)
	{
		if(_idx == 0)
			return mControlPositive;
		else if(_idx == 1)
			return mControlNegative;

		return NULL;
	}

	bool iInputAxis::IsTriggered()
	{
		return (TriggeredAmount() < -GetThreshold())
			|| (TriggeredAmount() > GetThreshold());
	}

	float clamp(float a, float b, float v)
	{
		if(v < a)
			return a;

		if(v > b)
			return b;

		return v;
	}

	void iInputAxis::TriggerAmount(float _amt)
	{
		_amt += mfOffset;
		if(_amt > 0)
		{
			_amt -= mfDeadZone;
			_amt /= mfRange;
			_amt = clamp(0, 1, _amt);
		}
		else
		{
			_amt += mfDeadZone;
			_amt /= mfRange;
			_amt = clamp(-1, 0, _amt);
		}
		
		if(mfFunction != 1)
		{
			_amt = powf(_amt, mfFunction);
		}

		_amt *= mfScale;

		bool triggered = _amt < -GetThreshold();
		if(triggered != mControlNegative->IsTriggered())
		{
			mControlNegative->Trigger(triggered);
		}

		triggered = _amt > GetThreshold();
		if(triggered != mControlPositive->IsTriggered())
		{
			mControlPositive->Trigger(triggered);
		}

		for(tActionList::iterator i = mActions.begin(); i != mActions.end(); i++)
		{
			((cAxisAction*)(*i))->TriggerAmount(_amt);
		}
	}
};

