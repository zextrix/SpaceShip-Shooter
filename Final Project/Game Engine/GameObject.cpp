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

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "Transform.h"
#include "Controller.h"
#include "UpDown.h"
#include "EventManager.h"
#include "Body.h"
#include"LeftRight.h"
#include "ObjectFactory.h"
#include"Timer.h"

extern ObjectFactory *gpOF;
extern Timer *gpTime;
extern int player_lives;


GameObject::GameObject()
{
	for (auto z : LComponent)
		z = nullptr;
}


GameObject::~GameObject()
{
	for (auto z : LComponent)
		delete z;
}


Component * GameObject::addComponent(unsigned int type)
{
	Component *MpNewComponent = nullptr;
	switch (type)
	{
	case TRANSFORM:
		MpNewComponent = new Transform();
		break;
	case SPRITE:
		MpNewComponent = new Sprite();
		break;
	case UPDOWN:
		MpNewComponent = new UpDown();
		break;
	case CONTROLLER:
		MpNewComponent = new Controller();
		break;
	case BODY:
		MpNewComponent = new Body();
		break;
	case LEFTRIGHT:
		MpNewComponent = new LeftRight();
		break;
	}

	if (MpNewComponent != nullptr)
	{
		LComponent.push_back(MpNewComponent);
		MpNewComponent->mpOwner = this;
	}

	return MpNewComponent;
}

Component * GameObject::getComponent(unsigned int type)
{
	for (auto z : LComponent)
	{
		if (z->GetType() == type)
			return z;
	}
	return nullptr;
}

void GameObject::HandleEvent(Event * pEvent)
{
	for (auto c : LComponent) 
	{
		c->HandleEvent(pEvent);
	}
}

void GameObject::Update()
{
	if (objType == ENEMY)
	{
		float frameTime = (float)gpTime->GetFrameTime();
		mTimer -= frameTime / 1000.0f;
		if (mTimer < 0.0f) 
		{

			Body *pBody = static_cast<Body *> (getComponent(BODY));
			Transform *pTr = static_cast<Transform *> (getComponent(TRANSFORM));

			GameObject * pGameObject = gpOF->CreateRunTimeObject("Bomb.txt");
			Transform * newPtr = static_cast<Transform *> (pGameObject->getComponent(TRANSFORM));

			Body *newPbody = static_cast<Body *> (pGameObject->getComponent(BODY));

			/*newPtr->mxPos = pTr->mxPos;		newPtr->myPos = pTr->myPos;

			newPtr->mxScale = 50.0f;				newPtr->myScale = 50.0f;
			newPbody->mPosX = pTr->mxPos;		newPbody->mPosY = pTr->myPos;*/

			newPtr->mxPos = pTr->mxPos;		newPtr->myPos = pTr->myPos - 30.0f;
			newPtr->mxScale = 25.0f;				newPtr->myScale = 25.0f;
			newPbody->mPosX = pTr->mxPos;		newPbody->mPosY = pTr->myPos - 30.0f;

			newPbody->mVelY -= 100.0f;

			mTimer = 6.0f;
		}

	}
	
	for (auto z : LComponent)
		z->Update();
}