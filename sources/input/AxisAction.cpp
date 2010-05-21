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

#include "input/AxisAction.h"
#include "input/InputAxis.h"

namespace hpl
{
	cAxisAction::cAxisAction(tString _name, cActionGroup *_grp): cAction(_name, _grp)
	{
		mfTriggeredAmount = 0;
	}

	cAxisAction::~cAxisAction()
	{
	}

	float cAxisAction::TriggeredAmount()
	{
		return mfTriggeredAmount;
	}

	void cAxisAction::TriggerAmount(float _amt)
	{
		if(GetInverted())
			_amt = -_amt;

		mfTriggeredAmount = _amt;
	}

	bool cAxisAction::AddControl(iInputControl *_ctrl)
	{
		if(dynamic_cast<iInputAxis*>(_ctrl) == NULL)
			return false;

		return cAction::AddControl(_ctrl);
	}
};
