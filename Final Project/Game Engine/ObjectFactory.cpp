/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:   ObjectFactory

Purpose:
To create the objects of the game world by serializing them, i.e loading data values of the world from a file

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

#include "ObjectFactory.h"


#include <stdio.h>
#include <string>
#include <cstring>

#include "GameObjectManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "Body.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include <random>

extern GameObjectManager *gpGOM;
extern float inGameTime;
extern ResourceManager *gpRM;


ObjectFactory::ObjectFactory()
{
}


ObjectFactory::~ObjectFactory()
{
	deleteObject.clear();

	for (auto go : runTimeObjects)
		delete go;
	runTimeObjects.clear();

	for (auto go : objectList)
		delete go.second;
	objectList.clear();
}

void ObjectFactory::LoadLevel(const char * pFileName)
{
	
	FILE *fp;
	std::string filePath = "./Resources/";
	filePath += pFileName;
	fopen_s(&fp, filePath.c_str(), "r");

	if (fp)
	{
		while (!feof(fp))
		{
			char objectFileName[256] = { 0 };
			//Get Gameobject

			fscanf_s(fp, "%255s\n", objectFileName, sizeof(objectFileName));
			std::string strObjFile = objectFileName;

			GameObject *pGameObject = LoadObject(strObjFile.c_str(),true);

			//Override transform values from level file

			Transform *pTrs = static_cast<Transform *>(pGameObject->getComponent(TRANSFORM));
			pTrs->Serialize(&fp);
			//Getting body and initializing its properties
			Body * pBody = static_cast<Body *>(pGameObject->getComponent(BODY));
			if(pBody!=nullptr)
				pBody->Initialize();
		}
		fclose(fp);
	}
}

void ObjectFactory::LoadListOfGameObject(const char * pFileName)
{
	FILE *fp;
	std::string filePath = "./Resources/";
	filePath += pFileName;
	fopen_s(&fp, filePath.c_str(), "r");

	if (fp)
	{
		while (!feof(fp))
		{
			char objectFileName[256] = { 0 };

			fscanf_s(fp, "%255s\n", objectFileName, sizeof(objectFileName));
			std::string strObjFile = objectFileName;

			if (strObjFile == "Winner.txt")
			{
				std::string filer = "./Resources/Screens/winner.png";
				wintexture = gpRM->LoadTexture(filer);
				VAOwinner = gpRM->LoadMesh("Square");
			}
			if (strObjFile == "Loser.txt")
			{
				std::string filer = "./Resources/Screens/gameover.png";
				losetexture = gpRM->LoadTexture(filer);
				VAOloser = gpRM->LoadMesh("Square");
			}
			if (strObjFile == "Start.txt")
			{
				std::string filer = "./Resources/Screens/CONTROL.png";
				starttexture = gpRM->LoadTexture(filer);
				VAOstart = gpRM->LoadMesh("Square");
			}


			objectList[objectFileName] = LoadObject(objectFileName,false);
			

		}
		
	}
	fclose(fp);
}
GameObject * ObjectFactory::CreateRunTimeObject(std::string pFileName)
{
	GameObject* runTimeObj;
	runTimeObj = LoadObject(pFileName.c_str(),false);
	
	runTimeObjects.push_back(runTimeObj);
	return runTimeObj;
}
void ObjectFactory::DeleteGameObject(GameObject * gameObject)
{
	deleteObject.push_back(gameObject);
}

void ObjectFactory::Update()
{
	if (inGameTime > 66.0f)
	{
		std::vector<GameObject *>::iterator it;
		for (it = gpGOM->LGameObject.begin(); it != gpGOM->LGameObject.end(); ++it)
		{
			if ((*it)->objType == PLAYER)//check if enemy type is there
				DeleteGameObject(*it);
		}
	}
	displayTime(inGameTime);
	
	AlienSpawner();
	
	AsterSpawner();
	
	PowerUp();

	for (auto go : runTimeObjects) {
		gpGOM->LGameObject.push_back(go);
	}
	runTimeObjects.clear();

	for (auto go : deleteObject) 
	{
		std::vector<GameObject *>::iterator itr = std::find(gpGOM->LGameObject.begin(),
			gpGOM->LGameObject.end(),
			go);
		if (itr != gpGOM->LGameObject.end()) 
		{
			gpGOM->LGameObject.erase(itr);
			delete go;
		}
	}
	deleteObject.clear();
}


GameObject * ObjectFactory::LoadObject(const char * pFileName,bool gom)
{
	GameObject *pnewGameObject = nullptr;

	FILE *fp;
	std::string filePath = "./Resources/";
	filePath += pFileName;
	fopen_s(&fp, filePath.c_str(), "r");
	if (fp)
	{
		pnewGameObject = new GameObject();

		while (!feof(fp))
		{
			char compName[256] = { 0 };
			fscanf_s(fp, "%255s\n", compName, sizeof(compName));

			std::string strCompName = compName;

			Component *pnewComp = nullptr;

			if (strCompName == "Transform")
				pnewComp = pnewGameObject->addComponent(TRANSFORM);
			if (strCompName == "Sprite")
				pnewComp = pnewGameObject->addComponent(SPRITE);
			if (strCompName == "Controller")
				pnewComp = pnewGameObject->addComponent(CONTROLLER);
			if (strCompName == "UpDown")
				pnewComp = pnewGameObject->addComponent(UPDOWN);
			if (strCompName == "LeftRight")
				pnewComp = pnewGameObject->addComponent(LEFTRIGHT);
			if(strCompName == "Body")
				pnewComp = pnewGameObject->addComponent(BODY);


			if (strCompName == "Player")
			{
				pnewGameObject->objType = PLAYER;
			}
			if (strCompName == "Ground")
			{
				pnewGameObject->objType = GROUND;
			}
			if (strCompName == "Enemy")
			{
				pnewGameObject->objType = ENEMY;
			}
			if (strCompName == "Bullet")
			{
				pnewGameObject->objType = BULLET;
			}
			if (strCompName == "LeftWall")
			{
				pnewGameObject->objType = WALLLEFT;
			}
			if (strCompName == "RightWall")
			{
				pnewGameObject->objType = WALLRIGHT;
			}
			if (strCompName == "Bomb")
			{
				pnewGameObject->objType = BOMB;
			}
			if (strCompName == "Asteroid")
			{
				pnewGameObject->objType = ASTER;
			}
			if (strCompName == "Speed")
			{
				pnewGameObject->objType = SPEED;
			}
			if (strCompName == "Tri")
			{
				pnewGameObject->objType = TRI;
			}
			


			if (pnewComp != nullptr)
			{
				pnewComp->Serialize(&fp);
			}
		}
		fclose(fp);
		if(gom)
		gpGOM->LGameObject.push_back(pnewGameObject);
		return pnewGameObject;
	}
	return nullptr;
}


void ObjectFactory::displayTime(float time)
{
	int Time = (int)time-5;
	

	if (Time != prevTime)
	{
		deleteObject.push_back(temp);
		temp = nullptr;
	}

	else
	{
		if (temp == nullptr)
		{
			std::string ntime = "./Resources/times/";
			std::string t = std::to_string(Time);
			ntime = ntime + t + ".png";//1.png

			GameObject *newtime = new GameObject();

			newtime->addComponent(TRANSFORM);
			Transform *pTrs = static_cast<Transform *> (newtime->getComponent(TRANSFORM));
			pTrs->mxPos = 720;
			pTrs->myPos = 550;
			pTrs->mxScale = 20;
			pTrs->myScale = 20;

			newtime->addComponent(SPRITE);
			Sprite *psp = static_cast<Sprite *> (newtime->getComponent(SPRITE));
			psp->texture = gpRM->LoadTexture(ntime.c_str());
			psp->vao = gpRM->LoadMesh("Square");

			newtime->objType = TIME;

			temp = newtime;
			runTimeObjects.push_back(newtime);
		}
	}

	prevTime = Time;
	
}

void ObjectFactory::AlienSpawner()
{
	int ct = 0;
	std::vector<GameObject *>::iterator it;
	for (it = gpGOM->LGameObject.begin(); it != gpGOM->LGameObject.end(); ++it)
	{
		if ((*it)->objType == ENEMY)//check if enemy type is there
			ct = 1;
	}
	if (ct==0)
	{
		GameObject* newenemy = CreateRunTimeObject("Enemy.txt");
		if (newenemy != nullptr)
		{
			const int range_from = 280;
			const int range_to = 720;
			std::random_device                  rand_dev;
			std::mt19937                        generator(rand_dev());
			std::uniform_int_distribution<int>  distr(range_from, range_to);

			int xpos = distr(generator);

			Transform * newPtr = static_cast<Transform *> (newenemy->getComponent(TRANSFORM));
			Body *newPbody = static_cast<Body *> (newenemy->getComponent(BODY));

			newPtr->mxPos = xpos;
			newPtr->myPos = 700;
			newPtr->mxScale = 50;
			newPtr->myScale = 50;
			newPbody->mPosX = xpos;
			newPbody->mPosY = 700;
		}
	}

}

void ObjectFactory::AsterSpawner()
{
	int ct = 0;
	std::vector<GameObject *>::iterator it;
	for (it = gpGOM->LGameObject.begin(); it != gpGOM->LGameObject.end(); ++it)
	{
		if ((*it)->objType == ASTER)//check if enemy type is there
			ct = 1;
	}
	if (ct == 0)
	{
		GameObject* newenemy = CreateRunTimeObject("Asteroid.txt");
		if (newenemy != nullptr)
		{
			const int range_from = 280;
			const int range_to = 720;
			std::random_device                  rand_dev;
			std::mt19937                        generator(rand_dev());
			std::uniform_int_distribution<int>  distr(range_from, range_to);

			int xpos = distr(generator);

			Transform * newPtr = static_cast<Transform *> (newenemy->getComponent(TRANSFORM));
			Body *newPbody = static_cast<Body *> (newenemy->getComponent(BODY));

			newPtr->mxPos = xpos;
			newPtr->myPos = 700;
			newPtr->mxScale = 50;
			newPtr->myScale = 50;
			newPbody->mPosX = xpos;
			newPbody->mPosY = 700;
		}
	}

}

void ObjectFactory::PowerUp()
{
	int Time = (int)inGameTime-5;
	if (Time % 10 == 0)
	{
		int ct = 0;
		std::vector<GameObject *>::iterator it;
		for (it = gpGOM->LGameObject.begin(); it != gpGOM->LGameObject.end(); ++it)
		{
			if ((*it)->objType == SPEED||(*it)->objType==TRI)//check if enemy type is there
				ct = 1;
		}

		const int from = 0;
		const int to = 10;
		std::random_device                  rd;
		std::mt19937                        generator(rd());
		std::uniform_int_distribution<int>  distr(from,to);

		int prob = distr(generator);

		if (ct == 0 && prob>5)
		{
			GameObject* newenemy = CreateRunTimeObject("Speed.txt");
			if (newenemy != nullptr)
			{
				const int range_from = 280;
				const int range_to = 720;
				std::random_device                  rand_dev;
				std::mt19937                        generator(rand_dev());
				std::uniform_int_distribution<int>  distr(range_from, range_to);

				int xpos = distr(generator);

				Transform * newPtr = static_cast<Transform *> (newenemy->getComponent(TRANSFORM));
				Body *newPbody = static_cast<Body *> (newenemy->getComponent(BODY));

				newPtr->mxPos = xpos;
				newPtr->myPos = 700;
				newPtr->mxScale = 50;
				newPtr->myScale = 50;
				newPbody->mPosX = xpos;
				newPbody->mPosY = 700;
			}
		}
		if (ct == 0 && prob < 6)
		{
			GameObject* newenemy = CreateRunTimeObject("TriBul.txt");
			if (newenemy != nullptr)
			{
				const int range_from = 280;
				const int range_to = 720;
				std::random_device                  rand_dev;
				std::mt19937                        generator(rand_dev());
				std::uniform_int_distribution<int>  distr(range_from, range_to);

				int xpos = distr(generator);

				Transform * newPtr = static_cast<Transform *> (newenemy->getComponent(TRANSFORM));
				Body *newPbody = static_cast<Body *> (newenemy->getComponent(BODY));

				newPtr->mxPos = xpos;
				newPtr->myPos = 600;
				newPtr->mxScale = 45;
				newPtr->myScale = 40;
				newPbody->mPosX = xpos;
				newPbody->mPosY = 600;
			}
		}
	}
}

