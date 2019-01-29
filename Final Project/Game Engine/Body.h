/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:   Body

Purpose:
To implement body component of game object

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
#include "GameObject.h"
class Shape;
class Body : public Component
{
public:
	Body();
	~Body();
	void Update();
	void Serialize(FILE **fpp);
	void Initialize();
	void Integrate(float DeltaTime);
	Component* ReturnThis();
public:
	float mPosX, mPosY;
	float mPrevPosX, mPrevPosY;
	float mVelX, mVelY;
	float mAccX, mAccY;
	float mTotalForceX, mTotalForceY;
	float mMass, mInvMass;
	Shape * mpShape;
	float gravity = 5.0f;
};

