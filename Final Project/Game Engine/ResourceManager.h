/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    ResourceManager

Purpose:
To maintain the resources in the application

used in the application by loading and freeing surfaces

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
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <unordered_map>
#include <GL/glew.h>

class Mesh;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	GLuint LoadMesh(std::string);
	GLuint LoadTexture(std::string);
	void DeleteTexture(std::string);

private:
	std::unordered_map<std::string, GLuint> LMeshes;
	std::unordered_map<std::string, GLuint> LTextures;

	//SDL_Surface *LoadSurface(const char *Filepath);
//private:
//	std::unordered_map<std::string, SDL_Surface*>LSurfaces;
};

#endif