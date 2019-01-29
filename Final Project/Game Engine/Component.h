/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    Component

Purpose:
To implement component based architecture

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
#include <stdio.h>

#include "EventManager.h"

enum COMPONENT_TYPE {
	TRANSFORM,
	SPRITE,
	CONTROLLER,
	UPDOWN,
	BODY,
	LEFTRIGHT
};
class Event;
class GameObject;
class Component
{
public:
	Component(unsigned int TYPE);
	virtual ~Component();
	virtual void Update() = 0;
	unsigned int GetType() { return mType; }
	virtual void Serialize(FILE **fp) {}
	virtual void HandleEvent(Event *) {};
	virtual Component* ReturnThis() = 0;
public:
	GameObject * mpOwner;

private:
	unsigned int mType;
};

