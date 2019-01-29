/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    Controller

Purpose:
To implement a controller to control the movements of the player gameobject

Language:   C++

Platform:

Compiler:-  Visual Studio 2017 - Visual C++ 14.1


Hardware Requirements:-		Display monitor, keyboard.

Operating System:-		Microsoft Windows 8.1+

Project:

Student Login:- pratyush.gawai
Class:- MSCS Fall2018
Assignment :- MileStone4

Author: Pratyush Gawai

Student login: pratyush.gawai

Student ID: 60001818

Creation date:  11/25/2018
---------------------------------------------------------*/

#pragma once
#include "Component.h"
class GameObject;
class Controller : public Component
{
public:
	Controller();
	~Controller();
	void Update();
	void HandleEvent(Event *);
	Component* ReturnThis();

	float tribtime = 0.0f;
	float spdtime = 0.0f;
	int speed = 100.0f;
	bool trib = true;
	bool mg = true;
};

