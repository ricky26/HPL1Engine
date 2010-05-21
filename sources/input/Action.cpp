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

#include "input/Action.h"
#include "input/InputControl.h"
#include "system/LowLevelSystem.h"

namespace hpl
{
	//////////////////////////////////////////////////////////////////////////
	// cActionGroup Implementation
	//////////////////////////////////////////////////////////////////////////

	cActionGroup::cActionGroup(tString _name, cActionGroup *_parent)
	{
		mName = _name;
	}

	tString cActionGroup::GetName()
	{
		return mName;
	}

	bool cActionGroup::AddAction(cAction *_act)
	{
		for(tActionList::iterator i = mActions.begin(); i != mActions.end(); i++)
		{
			if(*i == _act)
				return true;
		}

		mActions.push_back(_act);
		return true;
	}

	void cActionGroup::RemoveAction(cAction *_act)
	{
		for(tActionList::iterator i = mActions.begin(); i != mActions.end(); i++)
		{
			if(*i == _act)
			{
				mActions.erase(i);
				return;
			}
		}

	}

	size_t cActionGroup::ActionCount()
	{
		return mActions.size();
	}

	cAction *cActionGroup::GetAction(size_t _idx)
	{
		return mActions[_idx];
	}
	
	cAction *cActionGroup::FindAction(tString _name)
	{
		for(tActionList::iterator i = mActions.begin(); i != mActions.end(); i++)
		{
			if((*i)->GetName().compare(_name) == 0)
				return *i;
		}

		for(tGroupList::iterator i = mGroups.begin(); i != mGroups.end(); i++)
		{
			cAction *ret = (*i)->FindAction(_name);
			if(ret)
				return ret;
		}

		return NULL;
	}

	bool cActionGroup::AddGroup(cActionGroup *_act)
	{
		if(_act == this)
			return false;

		for(tGroupList::iterator i = mGroups.begin(); i != mGroups.end(); i++)
		{
			if(*i == _act)
				return true;
		}

		mGroups.push_back(_act);
		return true;
	}

	void cActionGroup::RemoveGroup(cActionGroup *_act)
	{
		for(tGroupList::iterator i = mGroups.begin(); i != mGroups.end(); i++)
		{
			if(*i == _act)
			{
				mGroups.erase(i);
				return;
			}
		}

	}

	size_t cActionGroup::GroupCount()
	{
		return mGroups.size();
	}

	cActionGroup *cActionGroup::GetGroup(size_t _idx)
	{
		return mGroups[_idx];
	}

	void cActionGroup::UnbindAll()
	{
		for(tActionList::iterator i = mActions.begin(); i != mActions.end(); i++)
		{
			(*i)->Unbind();
		}

		for(tGroupList::iterator i = mGroups.begin(); i != mGroups.end(); i++)
		{
			(*i)->UnbindAll();
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	cAction::cAction(tString _name, cActionGroup *_grp)
	{
		msName = _name;		
		mbBecameTriggered = false;
		mbWasTriggered = false;
		mbIsTriggered = false;
		mfLastClick = -1.0f;
		mfClickGap = -1.0f;
		miTriggerCount = 0;
		mbInverted = false;
		mpParent = NULL;

		if(_grp)
			if(_grp->AddAction(this))
				mpParent = _grp;
	}

	//-----------------------------------------------------------------------

	cAction::~cAction()
	{
		if(mpParent)
		{
			mpParent->RemoveAction(this);
			mpParent = NULL;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	// PRIVATE/PROTECTED METHODS
	//////////////////////////////////////////////////////////////////////////

	void cAction::Triggered(bool _val)
	{
		if(mbInverted)
			_val = !_val;

		if(_val == mbIsTriggered)
			return; // No extra triggers! -- Ricky26

		mbIsTriggered = _val;
		miTriggerCount++;

		//if(_val)
			mbBecameTriggered = _val;
		//else
			mbWasTriggered = !_val;

		float now = GetApplicationTime() / 1000.f;

		if(mfLastClick >= 0)
			mfClickGap = now - mfLastClick;

		mfLastClick = now;
	}

	bool cAction::AddControl(iInputControl *_ctrl)
	{
		for(tControlList::iterator i = mControls.begin(); i != mControls.end(); i++)
		{
			if(*i == _ctrl)
				return false;
		}

		mControls.push_back(_ctrl);
		return true;
	}

	void cAction::RemoveControl(iInputControl *_ctrl)
	{
		for(tControlList::iterator i = mControls.begin(); i != mControls.end(); i++)
		{
			if(*i == _ctrl)
			{
				mControls.erase(i);
				break;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

	bool cAction::Bind(iInputControl *_ctrl)
	{
		for(tControlList::iterator i = mControls.begin(); i != mControls.end(); i++)
		{
			if(*i == _ctrl)
				return true;
		}

		return _ctrl->AddAction(this);
	}
	
	//-----------------------------------------------------------------------

	void cAction::Unbind(iInputControl *_ctrl)
	{
		for(tControlList::iterator i = mControls.begin(); i != mControls.end(); i++)
		{
			if(*i == _ctrl)
			{
				(*i)->RemoveAction(this);
				return;
			}
		}
	}
	
	//-----------------------------------------------------------------------

	void cAction::Unbind()
	{
		for(tControlList::iterator i = mControls.begin(); i != mControls.end(); i++)
		{
			(*i)->RemoveAction(this);
		}
		mControls.clear();
	}
	
	//-----------------------------------------------------------------------

	size_t cAction::ControlCount()
	{
		return mControls.size();
	}

	//-----------------------------------------------------------------------

	iInputControl *cAction::GetControl(size_t _idx)
	{
		return mControls[_idx];
	}
	
	//-----------------------------------------------------------------------

	tString cAction::GetName()
	{
		return msName;
	}
	
	//-----------------------------------------------------------------------
	
	cActionGroup *cAction::GetGroup()
	{
		return mpParent;
	}

	//-----------------------------------------------------------------------
	
	bool cAction::GetInverted()
	{
		return mbInverted;
	}

	//-----------------------------------------------------------------------

	void cAction::SetInverted(bool _val)
	{
		if(_val == mbInverted)
			return; // So we don't cause unneccesary triggers! -- Ricky26

		bool curr = IsTriggered();
		mbInverted = _val;
		Triggered(curr); // This will now be the inverse of what it was. :D
	}

	//-----------------------------------------------------------------------

	bool cAction::IsTriggered()
	{
		return mbIsTriggered;
	}

	//-----------------------------------------------------------------------

	bool cAction::BecameTriggered()
	{
		if(mbBecameTriggered){
			mbBecameTriggered = false;
			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------

	bool cAction::WasTriggered()
	{
		if(mbWasTriggered){
			mbWasTriggered = false;
			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------

	int cAction::GetTriggerCount()
	{
		return miTriggerCount;
	}

	//-----------------------------------------------------------------------

	void cAction::ResetTriggerCount()
	{
		miTriggerCount = 0;
	}

	//-----------------------------------------------------------------------

	bool cAction::DoubleTriggered(float afLimit)
	{
		float now = GetApplicationTime() / 1000.f;

		return mfLastClick >= 0 && mfClickGap >= 0 && mfClickGap+(now-mfLastClick) < afLimit;
	}

	//-----------------------------------------------------------------------

	bool cAction::Held(float afLimit)
	{
		float now = GetApplicationTime() / 1000.f;

		return mfLastClick >= 0 && now-mfLastClick >= afLimit;
	}

	//-----------------------------------------------------------------------

	void cAction::Trigger()
	{
		Trigger(true);
		Trigger(false);
	}

	//-----------------------------------------------------------------------

	void cAction::Trigger(bool _val)
	{
		Triggered(_val);
	}

}
