/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:   Sprite

Purpose:
The UpDown property of the enemy gameobject

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
#include "UpDown.h"
#include "Timer.h"
#include "Transform.h"
#include "Controller.h"
#include "GameObject.h"

extern Timer *gpTime;
extern EventManager *gpEM;
UpDown::UpDown() : Component(UPDOWN)
{
	mGoingUp = true;
	mTimer = 0;
	mTimerLimit = 10000;
}

UpDown::~UpDown()
{
}

void UpDown::Update() {
	mTimer += gpTime->GetFrameTime();
	if (mTimer > mTimerLimit) {
		mGoingUp = !mGoingUp;
		mTimer = 0;
	}
	Transform * pTr = static_cast<Transform *> (mpOwner->getComponent(TRANSFORM));
	if (mGoingUp)
		pTr->myPos += 10;
	else
		pTr->myPos -= 10;
}

void UpDown::Serialize(FILE **fpp)
{
	int goingUp, timerLimit;
	fscanf_s(*fpp, "%i %i\n", &goingUp, &timerLimit);
	mGoingUp = (bool)goingUp;
	mTimerLimit = timerLimit;
}

void UpDown::HandleEvent(Event * pEvent) 
{
}

Component * UpDown::ReturnThis()
{
	return new UpDown(*this);
}
