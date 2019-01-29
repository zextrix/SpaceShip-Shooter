/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:   Sprite

Purpose:
The Sprite property of the gameobject

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

Creation date: 11/25/2018
---------------------------------------------------------*/

#include <string>
#include "Sprite.h"
#include "Timer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "ObjectFactory.h"

extern ResourceManager *gpRM;


Sprite::Sprite() : Component(SPRITE)
{
	texture = 0;
}


Sprite::~Sprite()
{
}

void Sprite::Update()
{
}

void Sprite::Serialize(FILE **fpp)
{
	char image[256];
	char shape[256];
	memset(image, 0, 256 * sizeof(char));

	std::string filePath = "./Resources/";
	fscanf_s(*fpp, "%255s\n", image, sizeof(image));//for the texture
	filePath += image;

	texture = gpRM->LoadTexture(filePath.c_str());

	std::string f = "./Resources/";
	fscanf_s(*fpp, "%255s\n", shape, sizeof(shape));//add this in the txt file for shape
	f += shape;
	vao = gpRM->LoadMesh(shape);
}

Component * Sprite::ReturnThis()
{
	return new Sprite(*this);
}
