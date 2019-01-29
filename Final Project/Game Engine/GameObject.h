/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    GameObject

Purpose:
To store every object in the game world as an gameobject

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
#include <vector>

enum GAMEOBJTYPE
{
	PLAYER,
	GROUND,
	ENEMY,
	BULLET,
	WALLLEFT,
	WALLRIGHT,
	BOMB,
	TIME,
	ASTER,
	SPEED,
	TRI
};

class Event;
class Component;
class GameObject
{
public:
	GameObject();
	~GameObject();

	Component * addComponent(unsigned int type);
	Component * getComponent(unsigned int type);
	void HandleEvent(Event *pEvent);
	void Update();

public:
	std::vector<Component *> LComponent;
	unsigned int objType;
	float mTimer;
};

