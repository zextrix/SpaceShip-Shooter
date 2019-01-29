/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    PhysicsManager

Purpose:
To implement physics in game

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
#include "EventManager.h"
#include"GameObject.h"
class SpeedUp : public Event
{
public:
	SpeedUp() : Event(SPEED_UP) {}
	~SpeedUp() {}
};
class TriBullet : public Event
{
public:
	TriBullet() : Event(TRI_BUL) {}
	~TriBullet() {}
};
class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();
	void Update(float);
	void Current(std::vector<GameObject *>);
	void DisplayLives(int lives);
	void DisplayPoints(int p);


	GameObject* livesdisp=nullptr;
	int prevLives = 3;
	GameObject* pointdisp=nullptr;
	int prevPoint = 0;
	
};

