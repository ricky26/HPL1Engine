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

#ifndef  HPL_JOYSTICK_SDL_H
#define  HPL_JOYSTICK_SDL_H

#include <vector>
#include "input/InputDevice.h"
#include "input/InputControl.h"
#include "input/InputAxis.h"
#include "input/InputHat.h"
#include "SDL/SDL.h"

namespace hpl
{
	class iLowLevelGraphics;
	class cLowLevelInputSDL;
	class cJoystickSDL;

	/**
	 * The class that represents a joystick axis.
	 */
	class cJoystickAxisSDL: public iInputAxis
	{
	public:
		friend class cJoystickSDL;

		cJoystickAxisSDL(cJoystickSDL *_parent, int _idx);
		
		virtual tString GetName();
		virtual float TriggeredAmount();

	protected:
		tString mName;
		cJoystickSDL *mpParent;
		int mIndex;
	};
	
	/**
	 * The class that represents a joystick hat.
	 */
	class cJoystickHatSDL: public iInputHat
	{
	public:
		friend class cJoystickSDL;

		cJoystickHatSDL(cJoystickSDL *_parent, int _idx);
		
		virtual tString GetName();
		virtual HatDirection TriggeredDirection();

	protected:
		tString mName;
		cJoystickSDL *mpParent;
		int mIndex;
	};
	
	/**
	 * The class that represents a joystick button.
	 */
	class cJoystickButtonSDL: public iInputControl
	{
	public:
		friend class cJoystickSDL;

		cJoystickButtonSDL(cJoystickSDL *_parent, int _idx);
		
		virtual tString GetName();
		virtual bool IsTriggered();

	protected:
		tString mName;
		cJoystickSDL *mpParent;
		int mIndex;
	};

	/**
	 * An SDL Joystick class, for controlling joysticks!
	 * @author Ricky Taylor
	 */
	class cJoystickSDL: public iInputDevice
	{
	public:
		typedef std::vector<cJoystickAxisSDL*> tAxisList;
		typedef std::vector<cJoystickHatSDL*> tHatList;
		typedef std::vector<cJoystickButtonSDL*> tButtonList;
		typedef std::vector<float> tAxes;
		typedef std::vector<int> tHats;
		typedef std::vector<bool> tButtons;

		cJoystickSDL(cLowLevelInputSDL *apLowLevelInputSDL, iLowLevelGraphics *apLowLevelGraphics, int _idx);
		virtual ~cJoystickSDL();

		virtual void Update();

		virtual size_t ChildCount();
		virtual iInputControl *GetChild(size_t);

		static iInputHat::HatDirection HatDirection(int _sdl);

		virtual float GetAxisValue(int _idx);
		virtual iInputHat::HatDirection GetHatValue(int _idx);
		virtual bool GetButtonValue(int _idx);

	protected:
		SDL_Joystick *mpJoystick;
		int mIndex;
	
		cLowLevelInputSDL *mpLowLevelInputSDL;
		iLowLevelGraphics *mpLowLevelGraphics;

		tAxisList mAxes;
		tAxes mAxisCache;
		tHatList mHats;
		tHats mHatCache;
		tButtonList mButtons;
		tButtons mButtonCache;
	};

};

#endif //HPL_JOYSTICK_SDL_H
