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

#ifndef HPL_ACTION_H
#define HPL_ACTION_H

#include <vector>
#include "system/SystemTypes.h"

namespace hpl
{
	class cAction;
	class cActionGroup
	{
	public:
		typedef std::vector<cAction*> tActionList;
		typedef std::vector<cActionGroup*> tGroupList;

		cActionGroup(tString _name, cActionGroup *_parent=NULL);

		tString GetName();

		bool AddAction(cAction *_act);
		void RemoveAction(cAction *_act);
		size_t ActionCount();
		cAction *GetAction(size_t _idx);
		cAction *FindAction(tString _name);

		bool AddGroup(cActionGroup *_grp);
		void RemoveGroup(cActionGroup *_grp);
		size_t GroupCount();
		cActionGroup *GetGroup(size_t _idx);

		void UnbindAll();

	protected:
		tString mName;
		cActionGroup *mpParent;
		tActionList mActions;
		tGroupList mGroups;
	};

	class iInputControl;
	class cAction
	{
	public:
		typedef std::vector<iInputControl *> tControlList;

		friend class iInputControl;

		cAction(tString _name, cActionGroup *_grp=NULL);
		virtual ~cAction();

		/**
		 *
		 * \return the name of the action.
		 */
		tString GetName();

		/**
		 * \return the action's group.
		 */
		cActionGroup *GetGroup();

		/**
		 * \return the control to which the action is currently attached.
		 */
		iInputControl *GetControl();
		
		/**
		 * \return whether the action is inverted.
		 */
		bool GetInverted();

		/**
		 * Set whether the action is inverted.
		 */
		void SetInverted(bool _inv);

		/**
		 * Filled in by the class that inherits from Action.
		 * \return true if the action is being triggered
		 */
		bool IsTriggered();

		/**
		 * \return the number of times the action has been triggered since the last
		 * trigger reset, or since the action was created.
		 */
		int GetTriggerCount();

		/**
		 * Reset the trigger count.
		 */
		void ResetTriggerCount();

		/**
		*
		* \return true if this is the first time this function has been called since the trigger
		*			was fired.
		*/
		bool BecameTriggered();

		/**
		*
		* \return true if this is the first time this function has been called since the trigger
		*			stopped firing.
		*/
		bool WasTriggered();

		/**
		*
		* \return true if the action just was double triggered (double clicked), else false.
		*/
		bool DoubleTriggered(float afLimit);

		/**
		*
		* \return true if the action has been held for a specified interval.
		*/
		bool Held(float afLimit);

		/**
		 * Bind ourselves to a control.
		 */
		bool Bind(iInputControl *_control);

		/**
		 * Unbind any bindings we have to a specific control.
		 */
		void Unbind(iInputControl *_control);

		/**
		 * Unbind any bindings we have.
		 */
		void Unbind();

		/**
		 * \return the number of controls we are connected to.
		 */
		size_t ControlCount();

		/**
		 * \return a control we are connected to.
		 */
		iInputControl *GetControl(size_t _idx);

		/**
		 * Computationally control the action.
		 */
		void Trigger();
		
		/**
		 * Computationally control the action.
		 */
		void Trigger(bool _val);

	protected:
		virtual void Triggered(bool _val);
		
		virtual bool AddControl(iInputControl *_ctrl);
		void RemoveControl(iInputControl *_ctrl);
			
	private:
		tString msName;
		tControlList mControls;
		cActionGroup *mpParent;
		
		int miTriggerCount;
		bool mbInverted;
		bool mbIsTriggered;
		bool mbBecameTriggered;
		bool mbWasTriggered;
		float mfLastClick;
		float mfClickGap;
	};

};
#endif // HPL_ACTION_H
