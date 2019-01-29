/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    Main

Purpose:
Point of entry for the application

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
#include <SDL.h>
#include "stdio.h"
#include <iostream>
#include <Windows.h>

#include "ResourceManager.h"
#include "InputManager.h"
#include "Timer.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "ObjectFactory.h"

#include "Transform.h"
#include "Sprite.h"
#include "Controller.h"
#include "Component.h"
#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include <GL/glew.h>
#define MAX_FRAME 60


int player_lives;
float inGameTime;
int points;

InputManager *gpIM = new InputManager();

ResourceManager *gpRM = new ResourceManager();

Timer *gpTime = new Timer(MAX_FRAME);

GameObjectManager *gpGOM = new GameObjectManager();

ObjectFactory *gpOF = new ObjectFactory();

EventManager *gpEM = new EventManager();

CollisionManager * gpCM = new CollisionManager();

PhysicsManager * gpPM = new PhysicsManager();

RenderManager * gpREM = nullptr;

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

int main(int argc, char* args[])
{
	SDL_Window *pWindow;

	int error = 0;
	int i,x = 0;

	player_lives = 3;
	points = 0;
	
	/*if (AllocConsole())
	{
		FILE* file;
		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle(L"SDL 2.0 Test");
	}*/
	
	bool appIsRunning = true;
	// Initialize SDL
	if((error = SDL_Init( SDL_INIT_VIDEO )) < 0 )
	{
		printf("Couldn't Initialize SDL, error %i\n", error);
		return 1;
	}
	

	pWindow = SDL_CreateWindow("FinalProject",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		800,										// w, in pixels
		600,										// h, in pixels
		SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

	// Check that the window was successfully made
	if (NULL == pWindow)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_GLContext context = SDL_GL_CreateContext(pWindow);

	//Initializing OpenGL subsystems
	gpREM = new RenderManager();

	float endtime = 0;
	
	gpOF->LoadLevel("Level1.txt");
	gpOF->LoadListOfGameObject("ObjectList.txt");
	
	// Game loop
	inGameTime = 0.0f;
	float frametime = 0.016f;
	while (true == appIsRunning)
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		gpTime->FrameStart();
		float frameTime = (float)gpTime->GetFrameTime();
		if (frameTime > 0)
			inGameTime += frametime;
		printf("FrameTime::%f\n", inGameTime);
		SDL_Event e;


		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				appIsRunning = false;
			}
			if (gpIM->IsPressed(SDL_SCANCODE_ESCAPE))
			{
				appIsRunning = false;
			}

		}

		if (inGameTime > 5.0f)
		{
			gpOF->Update();
			gpIM->Update();
			gpPM->Update(frameTime / 1000);
			gpEM->Update(frameTime / 1000);

			for (auto z : gpGOM->LGameObject)
				z->Update();
		}
		
		
		//gpREM->Background(gpOF->wintexture, gpOF->VAOwinner);
		if (inGameTime < 5.0f)
		{
			gpREM->Background(gpOF->starttexture, gpOF->VAOstart);
		}
		gpREM->Update();
		if (player_lives <= 0||points<10&&inGameTime>66)
		{
			endtime += 0.016f;
			gpREM->Background(gpOF->losetexture, gpOF->VAOloser);
			if (endtime > 5.0f)
				appIsRunning = false;
		}
		if (player_lives > 0 && points >= 10 && inGameTime > 66)
		{
			endtime += 0.016f;
			gpREM->Background(gpOF->wintexture, gpOF->VAOwinner);
			if (endtime > 5.0f)
				appIsRunning = false;
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		SDL_GL_SwapWindow(pWindow);
		glViewport(0, 0, 800, 600);

		gpTime->FrameEnd();
	}
	delete gpIM;
	delete gpTime;
	delete gpRM;
	delete gpGOM;
	delete gpOF;
	delete gpCM;
	delete gpPM;
	delete gpEM;
	delete gpREM;
	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();
	
	return 0;
}