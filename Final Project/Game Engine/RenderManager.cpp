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


#include "RenderManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Shader.h"
#include "Transform.h"
#include "Sprite.h"
#include "Body.h"
#include "CollisionManager.h"

#define _USE_MATH_DEFINES
#define PI 3.1415926535897932384626433832795
#include <math.h>

#include <iostream>
extern GameObjectManager * gpGOM;

glm::mat4 view(1);
glm::mat4 origin = glm::ortho(0.0f,800.0f,0.0f,600.0f, -1.0f, 1.0f);

RenderManager::RenderManager()
{
	Shader s;
	shaderColor = s.Initialize("shaderColor.vs", "shaderColor.fs");
	shaderTexture = s.Initialize("shaderTexture.vs", "shaderTexture.fs");
	text = true;
}

RenderManager::~RenderManager()
{
}

void RenderManager::Update() 
{
	Current(gpGOM->LGameObject);
}


void RenderManager::Current(std::vector<GameObject *> temp)
{
	for (auto go : temp)
	{
		Transform * pTr = static_cast<Transform *>(go->getComponent(TRANSFORM));
		Sprite * pSp = static_cast<Sprite *>(go->getComponent(SPRITE));
		Body *pbp = static_cast<Body *>(go->getComponent(BODY));
		if (pTr && pSp)
		{


			float x = pTr->mxPos;		float y = pTr->myPos;
			GLuint vao = pSp->vao;
			GLuint texture = pSp->texture;
			

			glm::vec3 v(x, y, 0.0f);
			glm::mat4 transform;
			glm::mat4 translatematrix(1);

			translatematrix = glm::translate(transform, v);

			transform = glm::translate(transform, v)

			*glm::rotate(transform, pTr->mAngle, glm::vec3(0.0f, 0.0f, 1.0f))
				
			*glm::scale(transform, glm::vec3(pTr->mxScale, pTr->myScale, 0.0f));

			glm::mat4 projection = origin * view;

			if (texture)
			{
				glUseProgram(shaderTexture);
				unsigned int utransform = glGetUniformLocation(shaderTexture, "transform");
				unsigned int uprojection = glGetUniformLocation(shaderTexture, "projection");
				unsigned int utextureOffSet = glGetUniformLocation(shaderTexture, "textureOffSet");
				unsigned int umulTexture = glGetUniformLocation(shaderTexture, "mulTexture");
				glUniform2f(umulTexture, 1, 1);
				glUniform2f(utextureOffSet, 0, 0);
				glUniformMatrix4fv(utransform, 1, GL_FALSE, glm::value_ptr(transform));
				glUniformMatrix4fv(uprojection, 1, GL_FALSE, glm::value_ptr(projection));
				glBindTexture(GL_TEXTURE_2D, texture);

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
			if (debug)
			{
				glUseProgram(shaderColor);
				unsigned int utransform = glGetUniformLocation(shaderColor, "transform");
				unsigned int uprojection = glGetUniformLocation(shaderColor, "projection");
				glUniformMatrix4fv(utransform, 1, GL_FALSE, glm::value_ptr(transform));
				glUniformMatrix4fv(uprojection, 1, GL_FALSE, glm::value_ptr(projection));
				glLineWidth(3.0f);
				glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);
			}
			
			glBindVertexArray(vao); 
			
			
		}
	}
}

void RenderManager::Background(unsigned int texture, unsigned int VAO) {

	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3(400.0f, 330.0f, 0.0f)) *
		glm::scale(transform, glm::vec3(800, 600, 0.0f));

	glm::mat4 projection = origin;

	glUseProgram(shaderTexture);
	unsigned int utransform = glGetUniformLocation(shaderTexture, "transform");
	unsigned int uprojection = glGetUniformLocation(shaderTexture, "projection");
	unsigned int utextureOffSet = glGetUniformLocation(shaderTexture, "textureOffSet");
	unsigned int umulTexture = glGetUniformLocation(shaderTexture, "mulTexture");
	glUniform2f(umulTexture, 1, 1);
	glUniform2f(utextureOffSet, 0, 0);
	glUniformMatrix4fv(utransform, 1, GL_FALSE, glm::value_ptr(transform));
	glUniformMatrix4fv(uprojection, 1, GL_FALSE, glm::value_ptr(projection));
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}