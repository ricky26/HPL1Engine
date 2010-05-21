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

#ifndef  HPL_INPUT_HAT_H
#define  HPL_INPUT_HAT_H

#include "input/InputAxis.h"

/**
 * Defines an axis of an input device.
 *
 * @author ricky26
 */

namespace hpl
{
	class iInputHat; // Forward Declaration
	class cInputHatAxis: public iInputAxis
	{
	public:
		enum HatAxis
		{
			TopBottom=0,
			LeftRight,
			TopRightBottomLeft,
			TopLeftBottomRight,
		};

		friend class iInputHat;

		cInputHatAxis(iInputHat *_parent, HatAxis _axis);

		// Properties
		virtual tString GetName();

		// Methods
		virtual float TriggeredAmount();

	protected:
		tString mName;
		iInputHat *mpParent;
		HatAxis mAxis;
	};

	/**
	 * An interface for an axis of an input device.
	 *
	 * @author ricky26
	 */
	class iInputHat: public iInputControl
	{
	public:
		enum HatDirection
		{
			Middle,
			TopLeft,
			Top,
			TopRight,
			Right,
			BottomRight,
			Bottom,
			BottomLeft,
			Left,
		};

		iInputHat(iInputDevice *_dev);
		virtual ~iInputHat();

		// Properties
		virtual size_t ChildCount();
		virtual iInputControl *GetChild(size_t);

		// Methods
		virtual bool IsTriggered();
		virtual HatDirection TriggeredDirection()=0;

	protected:
		virtual void TriggerDirection(HatDirection);

		cInputHatAxis *mAxisTB;
		cInputHatAxis *mAxisLR;
		cInputHatAxis *mAxisTLBR;
		cInputHatAxis *mAxisTRBL;
	};
};

#endif //HPL_INPUT_HAT_H
