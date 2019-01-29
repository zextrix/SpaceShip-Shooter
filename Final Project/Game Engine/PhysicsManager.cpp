/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:   PhysicsManager

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

#include "PhysicsManager.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "Body.h"
#include <iostream>
#include "Controller.h"
#include "ObjectFactory.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Sprite.h"


extern GameObjectManager * gpGOM;
extern CollisionManager * gpCM;
extern ObjectFactory* gpOF;
extern ResourceManager *gpRM;
extern int points;
extern int player_lives;

float fT;

PhysicsManager::PhysicsManager(){}


PhysicsManager::~PhysicsManager(){}


void PhysicsManager::Update(float frameTime) 
{
	fT = frameTime;
	Current(gpGOM->LGameObject);
	
	DisplayLives(player_lives);
	DisplayPoints(points);
	for (auto c : gpCM->mContacts)
	{
		
		 if (c->mpBodies[0]->mpOwner->objType == ENEMY && c->mpBodies[1]->mpOwner->objType == GROUND)
		 {
			gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
		 }

		 if (c->mpBodies[0]->mpOwner->objType == GROUND && c->mpBodies[1]->mpOwner->objType == ENEMY)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
		 }

		 if (c->mpBodies[0]->mpOwner->objType == ASTER && c->mpBodies[1]->mpOwner->objType == GROUND)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
		 }

		 if (c->mpBodies[0]->mpOwner->objType == GROUND && c->mpBodies[1]->mpOwner->objType == ASTER)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
		 }

		 if (c->mpBodies[0]->mpOwner->objType == BOMB && c->mpBodies[1]->mpOwner->objType == GROUND)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
		 }

		 if (c->mpBodies[0]->mpOwner->objType == GROUND && c->mpBodies[1]->mpOwner->objType == BOMB)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
		 }

		 if (c->mpBodies[0]->mpOwner->objType == BULLET && c->mpBodies[1]->mpOwner->objType == ENEMY)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
			 ++points;
		 }

		 if (c->mpBodies[0]->mpOwner->objType == ENEMY && c->mpBodies[1]->mpOwner->objType == BULLET)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
			 ++points;
		 }

		 if (c->mpBodies[0]->mpOwner->objType == BULLET && c->mpBodies[1]->mpOwner->objType == ASTER)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
			 ++points;
		 }

		 if (c->mpBodies[0]->mpOwner->objType == ASTER && c->mpBodies[1]->mpOwner->objType == BULLET)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
			 ++points;
		 }

		 if (c->mpBodies[0]->mpOwner->objType == ENEMY && c->mpBodies[1]->mpOwner->objType == PLAYER)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
			 
			 --player_lives;
			 if(player_lives<=0)
				 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
		 }

		 if (c->mpBodies[0]->mpOwner->objType == PLAYER && c->mpBodies[1]->mpOwner->objType == ASTER)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
			
			 --player_lives;
			 if(player_lives<=0)
				 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
		 }
		 if (c->mpBodies[0]->mpOwner->objType == ASTER && c->mpBodies[1]->mpOwner->objType == PLAYER)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
			 
			 --player_lives;
			 if (player_lives <= 0)
				 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
		 }

		 if (c->mpBodies[0]->mpOwner->objType == PLAYER && c->mpBodies[1]->mpOwner->objType == ENEMY)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
			 
			 --player_lives;
			 if (player_lives <= 0)
				 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
		 }

		 if (c->mpBodies[0]->mpOwner->objType == PLAYER && c->mpBodies[1]->mpOwner->objType == BOMB)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
			 
			 --player_lives;
			 if (player_lives <= 0)
				 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
		 }
		 if (c->mpBodies[0]->mpOwner->objType == BOMB && c->mpBodies[1]->mpOwner->objType == BULLET)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
		 }
		 if (c->mpBodies[1]->mpOwner->objType == BULLET && c->mpBodies[0]->mpOwner->objType == BOMB)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
		 }
		 if (c->mpBodies[1]->mpOwner->objType == SPEED && c->mpBodies[0]->mpOwner->objType == PLAYER)
		 {
			 SpeedUp s;
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
			 c->mpBodies[0]->mpOwner->HandleEvent(&s);
			 
		 }
		 if (c->mpBodies[1]->mpOwner->objType == PLAYER && c->mpBodies[0]->mpOwner->objType == SPEED)
		 {
			 SpeedUp s;
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
			 c->mpBodies[1]->mpOwner->HandleEvent(&s);
			 
		 }
		 if (c->mpBodies[1]->mpOwner->objType == TRI && c->mpBodies[0]->mpOwner->objType == PLAYER)
		 {
			 TriBullet t;
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
			 c->mpBodies[0]->mpOwner->HandleEvent(&t);
		 }
		 if (c->mpBodies[1]->mpOwner->objType == PLAYER && c->mpBodies[0]->mpOwner->objType == TRI)
		 {
			 TriBullet t;
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
			 c->mpBodies[1]->mpOwner->HandleEvent(&t);
		 }


		  if (c->mpBodies[1]->mpOwner->objType == SPEED && c->mpBodies[0]->mpOwner->objType == GROUND)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);
		 }
		 if (c->mpBodies[1]->mpOwner->objType == GROUND && c->mpBodies[0]->mpOwner->objType == SPEED)
		 {			
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);	
		 }
		 if (c->mpBodies[1]->mpOwner->objType == TRI && c->mpBodies[0]->mpOwner->objType == GROUND)
		 { 
			 gpOF->DeleteGameObject(c->mpBodies[1]->mpOwner);			
		 }
		 if (c->mpBodies[1]->mpOwner->objType == GROUND && c->mpBodies[0]->mpOwner->objType == TRI)
		 {
			 gpOF->DeleteGameObject(c->mpBodies[0]->mpOwner);
		 }
		 


		 if (c->mpBodies[0]->mpOwner->objType == PLAYER || c->mpBodies[1]->mpOwner->objType == PLAYER)
		 {
			c->Impulser();
			c->Correction();
		 }

	}
	
}

void PhysicsManager::Current(std::vector<GameObject *> temp) 
{
	//Integrate all Body Component
	for (auto go : temp)
	{
		Body * pBody = static_cast<Body *>(go->getComponent(BODY));
		if (nullptr != pBody)
		{
			pBody->Integrate(fT);
		}
	}

	//Reset previous Contacts
	gpCM->Reset();

	//Check for Intersections

	auto pObj1 = temp.begin();
	auto pObjLast = temp.end();
	for (; pObj1 != pObjLast; ++pObj1)
	{
		Body * pBody1 = static_cast<Body *>((*pObj1)->getComponent(BODY));

		if (nullptr == pBody1)
			continue;


		for (auto pObj2 = pObj1 + 1; pObj2 != pObjLast; ++pObj2)
		{
			Body * pBody2 = static_cast<Body *>((*pObj2)->getComponent(BODY));

			if (nullptr == pBody2 || ((*pObj1)->objType == (*pObj2)->objType))
				continue;
			if ((*pObj1)->objType == ENEMY && (*pObj2)->objType == BOMB)
				continue;
			if ( (*pObj1)->objType == PLAYER && (*pObj2)->objType == BULLET)
				continue;
			if (((*pObj2)->objType == BULLET) && pBody2->mPosY > 600.0f)
				gpOF->DeleteGameObject(*pObj2);
			if ((*pObj1)->objType == ENEMY && (*pObj2)->objType == ASTER)
				continue;
			if ((*pObj1)->objType == SPEED && (*pObj2)->objType == ENEMY)
				continue;
			if ((*pObj1)->objType == SPEED && (*pObj2)->objType == ASTER)
				continue;
			if ((*pObj1)->objType == TRI && (*pObj2)->objType == ENEMY)
				continue;
			if ((*pObj1)->objType == TRI && (*pObj2)->objType == ASTER)
				continue;
			
			
			gpCM->CheckCollisionAndGenerateContact(pBody1->mpShape, pBody1->mPosX, pBody1->mPosY,
				pBody2->mpShape, pBody2->mPosX, pBody2->mPosY);
		}
	}
}

void PhysicsManager::DisplayLives(int lives)
{

	if (lives != prevLives)
	{
		gpOF->DeleteGameObject(livesdisp);
		livesdisp = nullptr;
	}

	else
	{
		if (livesdisp == nullptr)
		{
			std::string ntime = "./Resources/times/";
			std::string t = std::to_string(lives);
			ntime = ntime + t + ".png";//1.png

			GameObject *newtime = new GameObject();

			newtime->addComponent(TRANSFORM);
			Transform *pTrs = static_cast<Transform *> (newtime->getComponent(TRANSFORM));
			pTrs->mxPos = 720;
			pTrs->myPos = 525;
			pTrs->mxScale = 20;
			pTrs->myScale = 20;

			newtime->addComponent(SPRITE);
			Sprite *psp = static_cast<Sprite *> (newtime->getComponent(SPRITE));
			psp->texture = gpRM->LoadTexture(ntime.c_str());
			psp->vao = gpRM->LoadMesh("Square");


			livesdisp = newtime;
			gpOF->runTimeObjects.push_back(newtime);
		}
	}

	prevLives = lives;
}

void PhysicsManager::DisplayPoints(int p)
{
	if (p != prevPoint)
	{
		gpOF->DeleteGameObject(pointdisp);
		pointdisp = nullptr;
	}

	else
	{
		if (pointdisp == nullptr)
		{
			std::string ntime = "./Resources/times/";
			std::string t = std::to_string(p);
			ntime = ntime + t + ".png";//1.png

			GameObject *newtime = new GameObject();

			newtime->addComponent(TRANSFORM);
			Transform *pTrs = static_cast<Transform *> (newtime->getComponent(TRANSFORM));
			pTrs->mxPos = 720;
			pTrs->myPos = 500;
			pTrs->mxScale = 20;
			pTrs->myScale = 20;

			newtime->addComponent(SPRITE);
			Sprite *psp = static_cast<Sprite *> (newtime->getComponent(SPRITE));
			psp->texture = gpRM->LoadTexture(ntime.c_str());
			psp->vao = gpRM->LoadMesh("Square");


			pointdisp = newtime;
			gpOF->runTimeObjects.push_back(newtime);
		}
	}

	prevPoint = p;
}
