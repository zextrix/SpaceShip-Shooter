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

#include "Controller.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "SDL_scancode.h"
#include "Body.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "PhysicsManager.h"
#include "Sprite.h"
#include "RenderManager.h"
#include "ObjectFactory.h"
#include "GameObjectManager.h"

extern InputManager *gpIM;
extern EventManager *gpEM;
extern RenderManager *gpREM;
extern ObjectFactory *gpOF;



Controller::Controller() :  Component(CONTROLLER)
{
	
}


Controller::~Controller()
{
}

void Controller::Update()
{
	tribtime += 0.016f;
	spdtime += 0.016f;
	if (nullptr != mpOwner && nullptr != gpIM)
	{
		Body *pBody = static_cast<Body *> (mpOwner->getComponent(BODY));
		Transform *pTr = static_cast<Transform *> (mpOwner->getComponent(TRANSFORM));
		Sprite *psp = static_cast<Sprite *> (mpOwner->getComponent(SPRITE));
		if (nullptr != pTr)
		{

			if (gpIM->IsTriggered(SDL_SCANCODE_W) && pBody->mVelY == 0)
			{
				pBody->mTotalForceY += 1500.0f;
			}


			if (gpIM->IsPressed(SDL_SCANCODE_A))
				pBody->mTotalForceX -= speed;
			else if (gpIM->IsPressed(SDL_SCANCODE_D))
				pBody->mTotalForceX += speed;



			if (gpIM->IsTriggered(SDL_SCANCODE_SPACE))
			{
				if (gpREM->debug)
					gpREM->debug = false;
				else
					gpREM->debug = true;
			}
			if (mg == true)
			{
				if (gpIM->IsTriggered(SDL_SCANCODE_K))
				{
					if (trib == false && tribtime < 3.0f)
					{
						GameObject * bullet1 = gpOF->CreateRunTimeObject("Bullet.txt");
						if (bullet1 != nullptr)
						{
							Transform * bPtr1 = static_cast<Transform *> (bullet1->getComponent(TRANSFORM));
							Body *bPbody1 = static_cast<Body *> (bullet1->getComponent(BODY));

							bPtr1->mxPos = pTr->mxPos + 20.0f;		bPtr1->myPos = pTr->myPos + 35.0f;
							bPtr1->mxScale = 25.0f;			        bPtr1->myScale = 25.0f;
							bPbody1->mPosX = pTr->mxPos + 20.0f;	    bPbody1->mPosY = pTr->myPos + 35.0f;
							bPbody1->mVelY += 200.0;
						}

						GameObject * bullet2 = gpOF->CreateRunTimeObject("Bullet.txt");
						if (bullet2 != nullptr)
						{
							Transform * bPtr2 = static_cast<Transform *> (bullet2->getComponent(TRANSFORM));
							Body *bPbody2 = static_cast<Body *> (bullet2->getComponent(BODY));

							bPtr2->mxPos = pTr->mxPos - 20.0f;		bPtr2->myPos = pTr->myPos + 35.0f;
							bPtr2->mxScale = 25.0f;					bPtr2->myScale = 25.0f;
							bPbody2->mPosX = pTr->mxPos - 20.0f;		bPbody2->mPosY = pTr->myPos + 35.0f;
							bPbody2->mVelY += 200.0;
						}
					}

					if (trib == true)
					{
						GameObject * bullet1 = gpOF->CreateRunTimeObject("Bullet.txt");
						if (bullet1 != nullptr)
						{
							Transform * bPtr1 = static_cast<Transform *> (bullet1->getComponent(TRANSFORM));
							Body *bPbody1 = static_cast<Body *> (bullet1->getComponent(BODY));

							bPtr1->mxPos = pTr->mxPos;		bPtr1->myPos = pTr->myPos + 35.0f;
							bPtr1->mxScale = 25.0f;			        bPtr1->myScale = 25.0f;
							bPbody1->mPosX = pTr->mxPos;	    bPbody1->mPosY = pTr->myPos + 35.0f;
							bPbody1->mVelY += 200.0;
						}
					}
				}
			}
			if (mg == false)
			{
				if (gpIM->IsPressed(SDL_SCANCODE_K))
				{
					GameObject * bullet1 = gpOF->CreateRunTimeObject("Bullet.txt");
					if (bullet1 != nullptr)
					{
						Transform * bPtr1 = static_cast<Transform *> (bullet1->getComponent(TRANSFORM));
						Body *bPbody1 = static_cast<Body *> (bullet1->getComponent(BODY));

						bPtr1->mxPos = pTr->mxPos + 20.0f;		bPtr1->myPos = pTr->myPos + 35.0f;
						bPtr1->mxScale = 25.0f;			        bPtr1->myScale = 25.0f;
						bPbody1->mPosX = pTr->mxPos + 20.0f;	    bPbody1->mPosY = pTr->myPos + 35.0f;
						bPbody1->mVelY += 200.0;
					}
				}
			}
		}
		if (tribtime > 3.0f)
			trib = true;
		if (spdtime > 1.8f)
		{
			mg = true;
		}
	}
}
void Controller::HandleEvent(Event * pEvent) 
{
	if (SPEED_UP == pEvent->mType)
	{
		spdtime = 0.0f;
		mg = false;
	}
	if (TRI_BUL == pEvent->mType)
	{
		tribtime = 0.0f;
		trib = false;
	}
}

Component * Controller::ReturnThis()
{
	return new Controller(*this);
}
