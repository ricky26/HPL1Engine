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
#include "impl/MouseSDL.h"

#include "SDL/SDL.h"

#include "graphics/LowLevelGraphics.h"
#include "impl/LowLevelInputSDL.h"

namespace hpl {

	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	cMouseSDL::cMouseSDL(cLowLevelInputSDL *apLowLevelInputSDL,iLowLevelGraphics *apLowLevelGraphics) : iMouse("Mouse")
	{
		mfMaxPercent = 0.7f;
		mfMinPercent = 0.1f;
		mlBufferSize = 6;

		mButtonCache = 0;

		mpLowLevelInputSDL = apLowLevelInputSDL;
		mpLowLevelGraphics = apLowLevelGraphics;

		mvMouseRelPos = cVector2f(0,0);
		mvMouseAbsPos = cVector2f(0,0);

		mbWheelUpMoved = false;
		mbWheelDownMoved = false;
	}

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////
	
	//-----------------------------------------------------------------------

	void cMouseSDL::Update()
	{
		cVector2f vScreenSize = mpLowLevelGraphics->GetScreenSize();
		cVector2f vVirtualSize = mpLowLevelGraphics->GetVirtualSize();

		std::list<SDL_Event>::iterator it = mpLowLevelInputSDL->mlstEvents.begin();
		for(; it != mpLowLevelInputSDL->mlstEvents.end(); ++it)
		{
			SDL_Event *pEvent = &(*it);
			bool mouseDown = false;
			switch(pEvent->type)
			{
			case SDL_MOUSEMOTION:
				{
					int x, y;

					SDL_GetMouseState(&x, &y);
					mvMouseAbsPos.x = (((float)x) * vVirtualSize.x) / vScreenSize.x;
					mvMouseAbsPos.y = (((float)y) * vVirtualSize.y) / vScreenSize.y;

					SDL_GetRelativeMouseState(&x, &y);
					mvMouseRelPos = cVector2f((float)x,(float)y);
					mvMouseRelPos = (mvMouseRelPos/vScreenSize)*vVirtualSize;
					
					mXAxis.TriggerDistance(pEvent->motion.x);
					mYAxis.TriggerDistance(pEvent->motion.y);
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouseDown = true;
				// Fall through
			case SDL_MOUSEBUTTONUP:
				{
					int btn = pEvent->button.button-1;
					int bit = 1 << btn;

					if(((mButtonCache & bit) == 0) == mouseDown) // ARGH!
					{
						if(mouseDown)
							mButtonCache |= bit;
						else
							mButtonCache &= ~bit;

						TriggerButton(btn, mouseDown);
					}
				}
				break;
			}
		}
	}
	
	//-----------------------------------------------------------------------
	
	bool cMouseSDL::ButtonIsDown(int mButton)
	{
		return (mButtonCache & (1 << mButton)) != 0;
	}

	//-----------------------------------------------------------------------

	cVector2f cMouseSDL::GetAbsPosition()
	{
		// Do a transform with the screen-size to the the float coordinates.  
		cVector2f vPos = mvMouseAbsPos;
		
		return vPos;
	}
	
	//-----------------------------------------------------------------------

	cVector2f cMouseSDL::GetRelPosition()
	{
		// Do a transform with the screen-size to the the float coordinates.  
		cVector2f vPos = mvMouseRelPos;
		//Ok this is?
		mvMouseRelPos = cVector2f(0,0);
		
		return vPos;
		/*cVector2f vNew;

		if((int)mlstMouseCoord.size() >= mlBufferSize)
			mlstMouseCoord.erase(mlstMouseCoord.begin());

		mlstMouseCoord.push_back(vPos);

		int lBufferSize = (int) mlstMouseCoord.size();

		cVector2f vSum(0,0);
		float fPercent = mfMinPercent;
		float fPercentAdd =  (mfMaxPercent - mfMinPercent)/((float)lBufferSize);
		float fTotalPercent=0;

		tVector2fListIt It = mlstMouseCoord.begin();
		while(It != mlstMouseCoord.end())
		{
			vSum.x +=It->x*fPercent;
			vSum.y +=It->y*fPercent;
			fTotalPercent+=fPercent;
			fPercent+=fPercentAdd;

			It++;
		}
		vNew.x = vSum.x/fTotalPercent;
		vNew.y = vSum.y/fTotalPercent;
		
		return vNew;*/
	}

	//-----------------------------------------------------------------------

	void cMouseSDL::Reset()
	{
		mlstMouseCoord.clear();
		mvMouseRelPos = cVector2f(0,0);

		int lX,lY; //Just to clear the rel pos.
		
		SDL_PumpEvents();
		SDL_GetRelativeMouseState(&lX, &lY);
	}
	
	//-----------------------------------------------------------------------

	void cMouseSDL::SetSmoothProperties(float afMinPercent, 
		float afMaxPercent,unsigned int alBufferSize)
	{
		mfMaxPercent = afMaxPercent;
		mfMinPercent = afMinPercent;
		mlBufferSize = alBufferSize;
	}
	
	//-----------------------------------------------------------------------
	
	/////////////////////////////////////////////////////////////////////////
	// PRIVATE METHODS
	/////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------
	
	//-----------------------------------------------------------------------

}
