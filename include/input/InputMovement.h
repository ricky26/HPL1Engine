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

#ifndef  HPL_INPUT_MOVEMENT_H
#define  HPL_INPUT_MOVEMENT_H

#include "InputControl.h"

/**
 * Defines an axis of an input device.
 *
 * @author ricky26
 */

namespace hpl
{
	/**
	 * An interface for a movement input (for example, mouse movement) along one axis.
	 *
	 * @author ricky26
	 */
	class iInputMovement: public iInputControl
	{
	public:
		iInputMovement(iInputDevice *_dev) : iInputControl(_dev) {}

		// Methods
		virtual bool IsTriggered();
		virtual float TriggeredDistance()=0;
		virtual void ResetDistance()=0;

	protected:
		virtual void TriggerDistance(float _mv);
	};
};

#endif //HPL_INPUT_MOVEMENT_H
