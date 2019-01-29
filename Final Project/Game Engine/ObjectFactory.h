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
#include <unordered_map>

#pragma once
class GameObject;
class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	GameObject *LoadObject(const char *pFileName,bool gom);
	void LoadLevel(const char *pFileName);
	void LoadListOfGameObject(const char *pFileName);
	void DeleteGameObject(GameObject *);
	GameObject * CreateRunTimeObject(std::string);
	void Update();
	std::unordered_map< std::string, GameObject *> objectList;
	std::vector<GameObject *> deleteObject;
	std::vector<GameObject *> runTimeObjects;
	
	void displayTime(float time);
	int prevTime=0;
	float my = 550.0f;
	GameObject* temp = nullptr;
	void AlienSpawner();
	void AsterSpawner();
	void PowerUp();

	unsigned int wintexture;
	unsigned int VAOwinner;

	unsigned int losetexture;
	unsigned int VAOloser;

	unsigned int starttexture;
	unsigned int VAOstart;
};

