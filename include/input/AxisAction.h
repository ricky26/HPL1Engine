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

#ifndef HPL_AXIS_ACTION_H
#define HPL_AXIS_ACTION_H

#include "input/Action.h"

namespace hpl
{
	class cAxisAction: public cAction
	{
	public:
		cAxisAction(tString _name, cActionGroup *_grp=NULL);
		virtual ~cAxisAction();

		/**
		 * \return the current value of the axis.
		 */
		float TriggeredAmount();

		/**
		 * Computationally control the action.
		 */
		void TriggerAmount(float _amt);

	protected:
		virtual bool AddControl(iInputControl *_ctrl);
			
	private:		
		float mfTriggeredAmount;
	};

};
#endif // HPL_AXIS_ACTION_H
