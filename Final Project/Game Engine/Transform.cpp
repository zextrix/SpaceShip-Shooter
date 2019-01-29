/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:   Transform

Purpose:
The Transform property of the gameobject

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

#include "Transform.h"
#include "ResourceManager.h"

extern ResourceManager *gpRM;

Transform::Transform() : Component(TRANSFORM)
{
	mxPos = myPos = 0.0f;
	mAngle = 0.0f;
}


Transform::~Transform(){}

void Transform::Update(){}


void Transform::Serialize(FILE **fp)
{
	fscanf_s(*fp, "%f %f %f %f\n", &mxPos, &myPos,&mxScale,&myScale);
}

Component * Transform::ReturnThis()
{
	return new Transform(*this);
}
