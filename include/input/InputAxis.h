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

#ifndef  HPL_INPUT_AXIS_H
#define  HPL_INPUT_AXIS_H

#include "input/InputControl.h"

/**
 * Defines an axis of an input device.
 *
 * @author ricky26
 */

namespace hpl
{
	class iInputAxis; // Forward Declaration
	class cInputAxisControl: public iInputControl
	{
	public:
		enum AxisControl
		{
			Positive=0,
			Negative,
		};

		friend class iInputAxis;

		cInputAxisControl(iInputAxis *_parent, AxisControl _axis);

		// Properties
		virtual tString GetName();

		// Methods
		virtual bool IsTriggered();

	protected:
		tString mName;
		iInputAxis *mpParent;
		AxisControl mAxis;
	};
	/**
	 * An interface for an axis of an input device.
	 *
	 * @author ricky26
	 */
	class iInputAxis: public iInputControl
	{
	public:
		iInputAxis(iInputDevice *_dev);
		virtual ~iInputAxis();

		// Properties
		virtual size_t ChildCount();
		virtual iInputControl *GetChild(size_t);
		virtual float GetThreshold() { return 0.7f; }

		// Configuration
		void SetFunction(float _fnc);
		float GetFunction();
		void SetOffset(float _amt);
		float GetOffset();
		void SetDeadZone(float _amt);
		float GetDeadZone();
		void SetCutoff(float _amt);
		float GetCutoff();
		float GetRange();
		void SetScale(float _amt);
		float GetScale();

		// Methods
		virtual bool IsTriggered();
		virtual float TriggeredAmount()=0;

	protected:
		virtual void TriggerAmount(float _amt);

		cInputAxisControl *mControlPositive;
		cInputAxisControl *mControlNegative;

		int mfFunction;
		float mfOffset;
		float mfDeadZone;
		float mfCutoff;
		float mfRange;
		float mfScale;
	};
};

#endif //HPL_INPUT_AXIS_H
