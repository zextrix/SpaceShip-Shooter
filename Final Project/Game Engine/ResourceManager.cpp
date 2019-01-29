/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    ResourceManager

Purpose:
To maintain the resources of the applicaation

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

#include "ResourceManager.h"
#include "RenderManager.h"
#include "Mesh.h"
#include <string>
#include "stb_image.h"
#include <iostream>

extern RenderManager * gpREM;
ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}

GLuint ResourceManager::LoadMesh(std::string shapeFile)
{
	//Check Hash map
	GLuint vao = LMeshes[shapeFile];

	//If Loaded
	if (vao) {
		return vao;
	}

	//Load 
	Mesh m;
	if (shapeFile == "Square")
	{
		vao = m.MakeSquare();
	}
	if (shapeFile == "Triangle") 
	{
		vao = m.MakeTriangle();
	}
	if (shapeFile == "Circle")
	{
		vao = m.MakeCircle();
	}

	//Load Success = Add to hash map
	if (vao) {
		LMeshes[shapeFile] = vao;
	}

	//return it
	return vao;
}

GLuint ResourceManager::LoadTexture(std::string textureFile)
{
	//Check Hash Map
	GLuint textureID = LTextures[textureFile];

	if (textureID) {
		return textureID;
	}

	//Load 
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID); 
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		int w, h, channels;
		
		stbi_set_flip_vertically_on_load(true);

		unsigned char *data = stbi_load(textureFile.c_str(), &w, &h, &channels, 0);

		if (data)
		{
			if (channels == 4)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}

		stbi_image_free(data);
	}

	
	if (textureID)
	{
		LTextures[textureFile] = textureID;
	}

	
	return textureID;
}

void ResourceManager::DeleteTexture(std::string textureFile)
{
	GLuint textureID = LTextures[textureFile];
	if (textureID)
	{
		std::unordered_map<std::string, GLuint>::iterator it = LTextures.begin();
		while (it != LTextures.end())
		{
			if (it->second == textureID)
			{
				break;
			}
			it++;
		}

		if (it != LTextures.end())
			LTextures.erase(it);
	}
}
