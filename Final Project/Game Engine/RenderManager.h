/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:   RenderManager

Purpose:
Deals with OpenGL subsystem

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
#include "GameObject.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class GameObjectManager;
class RenderManager
{
public:
	RenderManager();
	~RenderManager();
	void Update();
	void Current(std::vector<GameObject *>);
	bool text;
	bool debug=false;
	void Background(unsigned int texture, unsigned int VAO);
private:
	int shaderColor;
	int shaderTexture;
};
