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
#include "input/Input.h"
#include "input/InputAxis.h"
#include "system/LowLevelSystem.h"
#include "input/Mouse.h"
#include "input/Keyboard.h"
#include "input/LowLevelInput.h"
#include "input/Action.h"
#include "input/ActionKeyboard.h"
#include "input/ActionMouseButton.h"
#include "impl/tinyXML/tinyxml.h"


namespace hpl 
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------
	
	cInput::cInput(iLowLevelInput *apLowLevelInput) : iUpdateable("HPL_Input"),
		mRootActionGroup("Actions")
	{
		mpLowLevelInput = apLowLevelInput;

		mpKeyboard = mpLowLevelInput->GetKeyboard();
		mpMouse = mpLowLevelInput->GetMouse();

		mlstInputDevices.reserve(mpLowLevelInput->DeviceCount());
		for(iLowLevelInput::tCount i = 0; i < mpLowLevelInput->DeviceCount(); i++)
		{
			mlstInputDevices.push_back(mpLowLevelInput->GetDevice(i));
		}
	}

	//-----------------------------------------------------------------------
	
	cInput::~cInput()
	{
		Log("Exiting Input Module\n");
		Log("--------------------------------------------------------\n\n");
	}

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS				
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	void cInput::Update(float afTimeStep)
	{
		mpLowLevelInput->BeginInputUpdate();
		
		for(tInputDeviceListIt it = mlstInputDevices.begin(); it!= mlstInputDevices.end();++it)
		{
			(*it)->Update();
		}

		mpLowLevelInput->EndInputUpdate();
	}
	
	//-----------------------------------------------------------------------

	iKeyboard* cInput::GetKeyboard()
	{
		return mpKeyboard;
	}

	//-----------------------------------------------------------------------

	iMouse* cInput::GetMouse()
	{
		return mpMouse;
	}

	//-----------------------------------------------------------------------

	iInputDevice *cInput::FindDevice(tString _name)
	{
		for(tInputDeviceList::iterator it = mlstInputDevices.begin(); it != mlstInputDevices.end(); it++)
		{
			if((*it)->GetName().compare(_name) == 0)
				return *it;
		}

		return NULL;
	}

	//-----------------------------------------------------------------------
	
	cActionGroup *cInput::GetActionGroup()
	{
		return &mRootActionGroup;
	}

	//-----------------------------------------------------------------------

	bool cInput::CheckForInput()
	{
		for(tInputDeviceList::iterator it = mlstInputDevices.begin(); it != mlstInputDevices.end(); it++)
		{
			if((*it)->IsActive())
				return true;
		}

		return false;

		/*//////////////////////
		//Keyboard
		for(int i=0; i< eKey_LastEnum; ++i)
		{
			if(mpKeyboard->KeyIsDown((eKey)i)) return true;
		}

		//////////////////////
		//Mouse
		for(int i=0; i< eMButton_LastEnum; ++i)
		{
			if(mpMouse->ButtonIsDown((eMButton)i)) return true;
		}
		
		return false;*/
	}

	//-----------------------------------------------------------------------
	
	bool cInput::AssignControl(cAction *_action)
	{		
		for(tInputDeviceList::iterator it = mlstInputDevices.begin(); it != mlstInputDevices.end(); it++)
		{
			if((*it)->AssignControl(_action))
				return true;
		}

		return false;

		/*
		//////////////////////
		//Keyboard
		for(int i=0; i< eKey_LastEnum; ++i)
		{
			if(mpKeyboard->KeyIsDown((eKey)i))
			{
				pAction = hplNew( cActionKeyboard, (asName,this,(eKey)i));
				break;
			}
		}

		//////////////////////
		//Mouse
		if(pAction==NULL)
		{
			for(int i=0; i< eMButton_LastEnum; ++i)
			{
				if(mpMouse->ButtonIsDown((eMButton)i))
				{
					pAction = hplNew( cActionMouseButton, (asName,this,(eMButton)i));					
					break;
				}
			}
		}

		if(pAction)
		{
			iAction *pOldAction = GetAction(asName);
			if(pOldAction) hplDelete(pOldAction);

			m_mapActions.erase(asName);

			AddAction(pAction);
		}
		
		return pAction;*/


	}
	
	//-----------------------------------------------------------------------
	
	bool cInput::LoadLayout(tWString _path)
	{
		#ifdef WIN32
				FILE *pFile = _wfopen(_path.c_str(),_W("rb"));
		#else
				FILE *pFile = fopen(cString::To8Char(_path).c_str(),"rb");
		#endif

		if(!pFile)
			return false;
		
		TiXmlDocument xmlDoc;
		if(!xmlDoc.LoadFile(pFile))
		{
			fclose(pFile);
			return false;
		}

		// Load calibrations...
		TiXmlElement *currNode = xmlDoc.FirstChildElement("Calibration");
		while(currNode)
		{
			const char *rawName = currNode->Attribute("device");
			if(rawName)
			{
				tString deviceName(rawName);
				iInputDevice *device = FindDevice(deviceName);
				if(device)
				{
					rawName = currNode->Attribute("control");
					if(rawName)
					{
						tString controlName(rawName);
						iInputControl *control = device->FindControl(controlName);
						if(control)
						{
							iInputAxis *axis = dynamic_cast<iInputAxis*>(control);
							if(axis)
							{
								// Offset
								double val = 0;
								rawName = currNode->Attribute("offset", &val);
								if(rawName)
									axis->SetOffset((float)val);

								// DeadZone
								val = 0;
								rawName = currNode->Attribute("deadZone", &val);
								if(rawName)
									axis->SetDeadZone((float)val);

								// Cutoff
								val = 0;
								rawName = currNode->Attribute("cutoff", &val);
								if(rawName)
									axis->SetCutoff((float)val);

								// Scale
								val = 0;
								rawName = currNode->Attribute("scale", &val);
								if(rawName)
									axis->SetScale((float)val);

								// Function
								val = 0;
								rawName = currNode->Attribute("function", &val);
								if(rawName)
									axis->SetFunction((float)val);
							}
						}
						else
							Warning("Input: Calibration set on non-existant control '%s'!\n", rawName);
					}
					else
						Warning("Input: Calibration set without specifying control!\n");
				}
				else
					Warning("Input: Calibration set on non-existant device '%s'!\n", rawName);

			}
			else
				Warning("Input: Calibration set without specifying device!\n");
			
			currNode = currNode->NextSiblingElement("Calibration");
		}

		// Clear all actions of any bindings...
		mRootActionGroup.UnbindAll();

		// Load the new bindings...
		currNode = xmlDoc.FirstChildElement("Action");
		while(currNode)
		{
			const char *rawName = currNode->Attribute("name");
			if(rawName)
			{
				tString name(rawName);
				cAction *action = mRootActionGroup.FindAction(name);
				if(action)
				{
					TiXmlElement *currBind = currNode->FirstChildElement("Bind");
					while(currBind)
					{
						rawName = currBind->Attribute("device");
						if(rawName)
						{
							tString deviceName(rawName);
							iInputDevice *device = FindDevice(deviceName);
							if(device)
							{
								rawName = currBind->Attribute("control");
								if(rawName)
								{
									tString controlName(rawName);
									iInputControl *control = device->FindControl(controlName);
									if(control)
									{
										if(!action->Bind(control))
											Warning("Input: Failed to bind '%s' to '%s'...\n", name.c_str(), controlName.c_str());
									}
									else
										Warning("Input: Device '%s' has no such control '%s'! Skipping...\n", deviceName.c_str(), controlName.c_str());
								}
								else
									Warning("Input: No input control specified! Skipping...\n");

								int isInverted = -1;
								rawName = currBind->Attribute("inverted", &isInverted);
								if(rawName != NULL)
									action->SetInverted(isInverted == 1);
									
							}
							else
								Warning("Input: Input device '%s' not found, skipping bindings...\n", rawName);
						}
						else
							Warning("Input: Binding with no device name! Skipping...\n");

						currBind = currBind->NextSiblingElement("Bind");
					}
				}
				else
					Warning("Input: Action '%s' not found! Skipping...\n", rawName);
			}
			else
				Warning("Input: Action with no name! Skipping...\n");

			currNode = currNode->NextSiblingElement("Action");
		}

		return true;
	}

	//-----------------------------------------------------------------------

	bool cInput::SaveLayout(tWString _path)
	{
		return true;
	}

}
