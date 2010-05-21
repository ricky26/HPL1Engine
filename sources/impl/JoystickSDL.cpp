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

#include <sstream>
#include "system/LowLevelSystem.h"
#include "impl/JoystickSDL.h"
#include "impl/LowLevelInputSDL.h"

namespace hpl
{
	/////
	// cJoystickAxisSDL implementation.
	/////

	cJoystickAxisSDL::cJoystickAxisSDL(cJoystickSDL *_parent, int _idx): iInputAxis(_parent)
	{
		mpParent = _parent;
		mIndex = _idx;
			
		std::stringstream name;
		name << "Axis " << (_idx+1);
		mName = name.str();
	}

	tString cJoystickAxisSDL::GetName()
	{
		return mName;
	}

	float cJoystickAxisSDL::TriggeredAmount()
	{
		return mpParent->GetAxisValue(mIndex);
	}
	
	/////
	// cJoystickHatSDL implementation.
	/////

	cJoystickHatSDL::cJoystickHatSDL(cJoystickSDL *_parent, int _idx): iInputHat(_parent)
	{
		mpParent = _parent;
		mIndex = _idx;
			
		std::stringstream name;
		name << "Hat " << (_idx+1);
		mName = name.str();
	}

	tString cJoystickHatSDL::GetName()
	{
		return mName;
	}

	iInputHat::HatDirection cJoystickHatSDL::TriggeredDirection()
	{
		return mpParent->GetHatValue(mIndex);
	}

	/////
	// cJoystickButtonSDL implementation.
	/////

	cJoystickButtonSDL::cJoystickButtonSDL(cJoystickSDL *_parent, int _idx): iInputControl(_parent)
	{
		mpParent = _parent;
		mIndex = _idx;
			
		std::stringstream name;
		name << "Button " << (_idx+1);
		mName = name.str();
	}

	tString cJoystickButtonSDL::GetName()
	{
		return mName;
	}

	bool cJoystickButtonSDL::IsTriggered()
	{
		return mpParent->GetButtonValue(mIndex);
	}

	/////
	// cJoystickSDL implementation.
	/////

	cJoystickSDL::cJoystickSDL(cLowLevelInputSDL *apLowLevelInputSDL, iLowLevelGraphics *apLowLevelGraphics, int _idx): iInputDevice(SDL_JoystickName(_idx))
	{
		mpLowLevelInputSDL = apLowLevelInputSDL;
		mpLowLevelGraphics = apLowLevelGraphics;

		Log("Loading joystick '%s'...\n", GetName().c_str());

		mIndex = _idx;
		mpJoystick = SDL_JoystickOpen(_idx);

		if(mpJoystick)
		{
			int axes = SDL_JoystickNumAxes(mpJoystick);
			mAxes.reserve(axes);
			mAxisCache.reserve(axes);
			for(int i = 0; i < axes; i++)
			{
				cJoystickAxisSDL *axis = new cJoystickAxisSDL(this, i);
				mAxes.push_back(axis);
				mAxisCache.push_back(SDL_JoystickGetAxis(mpJoystick, i) / 32767.f);
			}

			int hats = SDL_JoystickNumHats(mpJoystick);
			mHats.reserve(hats);
			mHatCache.reserve(hats);
			for(int i = 0; i < hats; i++)
			{
				cJoystickHatSDL *hat = new cJoystickHatSDL(this, i);
				mHats.push_back(hat);
				mHatCache.push_back(SDL_JoystickGetHat(mpJoystick, i));
			}

			int buttons = SDL_JoystickNumButtons(mpJoystick);
			mButtons.reserve(buttons);
			mButtonCache.reserve(buttons);
			for(int i = 0; i < buttons; i++)
			{
				cJoystickButtonSDL *hat = new cJoystickButtonSDL(this, i);
				mButtons.push_back(hat);
				mButtonCache.push_back(SDL_JoystickGetButton(mpJoystick, i));
			}

			Log("Joystick has:\n\t%d Axes\n\t%d Hats\n\t%d Buttons\n...\n", axes, hats, buttons);
		}
	}

	cJoystickSDL::~cJoystickSDL()
	{
		if(mpJoystick)
		{
			SDL_JoystickClose(mpJoystick);
			mpJoystick = NULL;
		}

		STLDeleteAll(mAxes);
		STLDeleteAll(mHats);
		STLDeleteAll(mButtons);
	}

	void cJoystickSDL::Update()
	{
		std::list<SDL_Event>::iterator it = mpLowLevelInputSDL->mlstEvents.begin();
		for(; it != mpLowLevelInputSDL->mlstEvents.end(); ++it)
		{
			SDL_Event *pEvent = &(*it);
			bool buttonDown = false;
			switch(pEvent->type)
			{
			case SDL_JOYAXISMOTION:
				if(pEvent->jaxis.which == mIndex)
				{
					float val = pEvent->jaxis.value / 32767.f;
					mAxes[pEvent->jaxis.axis]->TriggerAmount(val);
					mAxisCache[pEvent->jaxis.axis] = val;
				}
				break;

			case SDL_JOYHATMOTION:
				if(pEvent->jhat.which == mIndex)
				{
					if(mHatCache[pEvent->jhat.hat] != pEvent->jhat.value)
					{
						mHats[pEvent->jhat.hat]->TriggerDirection(HatDirection(pEvent->jhat.value));
						mHatCache[pEvent->jhat.hat] = pEvent->jhat.value;
					}
				}
				break;

			case SDL_JOYBUTTONDOWN:
				buttonDown = true;
				// Fall through
			case SDL_JOYBUTTONUP:
				if(pEvent->jbutton.which == mIndex)
				{
					if(mButtonCache[pEvent->jbutton.button] != buttonDown)
					{
						mButtons[pEvent->jbutton.button]->Trigger(buttonDown);
						mButtonCache[pEvent->jbutton.button] = buttonDown;
					}
				}
				break;
			}
		}
	}

	size_t cJoystickSDL::ChildCount()
	{
		int count = mAxes.size() + mHats.size() + mButtons.size();
		
		if(mAxes.size() > 0)
			count += mAxes[0]->ChildCount()*mAxes.size();

		if(mHats.size() > 0)
			count += mHats[0]->ChildCount()*mHats.size();

		return count;
	}

	iInputControl *cJoystickSDL::GetChild(size_t _idx)
	{
		if(_idx < mAxes.size())
			return mAxes[_idx];
		_idx -= mAxes.size();

		if(_idx < mHats.size())
			return mHats[_idx];
		_idx -= mHats.size();

		if(_idx < mButtons.size())
			return mButtons[_idx];
		_idx -= mButtons.size();

		if(mAxes.size() > 0)
		{
			int kids = mAxes[0]->ChildCount();
			int size = kids * mAxes.size();
			if(_idx < size)
			{
				int mod = _idx % kids;
				int base = _idx/kids;
				return mAxes[base]->GetChild(mod);
			}

			_idx -= size;
		}

		if(mHats.size() > 0)
		{
			int kids = mHats[0]->ChildCount();
			int size = kids * mHats.size();
			if(_idx < size)
			{
				int mod = _idx % kids;
				int base = _idx/kids;
				return mHats[base]->GetChild(mod);
			}

			_idx -= size;
		}

		return NULL;
	}

	iInputHat::HatDirection cJoystickSDL::HatDirection(int _sdl)
	{
		switch(_sdl)
		{
		case SDL_HAT_UP:
			return iInputHat::Top;

		case SDL_HAT_RIGHT:
			return iInputHat::Right;

		case SDL_HAT_DOWN:
			return iInputHat::Bottom;

		case SDL_HAT_LEFT:
			return iInputHat::Left;

		case SDL_HAT_RIGHTUP:
			return iInputHat::TopRight;

		case SDL_HAT_RIGHTDOWN:
			return iInputHat::BottomRight;

		case SDL_HAT_LEFTUP:
			return iInputHat::TopLeft;

		case SDL_HAT_LEFTDOWN:
			return iInputHat::BottomLeft;

		default:
			return iInputHat::Middle;
		}
	}

	float cJoystickSDL::GetAxisValue(int _idx)
	{
		return mAxisCache[_idx];
	}

	iInputHat::HatDirection cJoystickSDL::GetHatValue(int _idx)
	{
		return HatDirection(mHatCache[_idx]);
	}

	bool cJoystickSDL::GetButtonValue(int _idx)
	{
		return mButtonCache[_idx];
	}
};

