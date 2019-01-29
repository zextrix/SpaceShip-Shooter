/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    InputManager

Purpose:
To check for inputs on pressing,releasing and triggering keys

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
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "SDL_keyboard.h"
class InputManager
{
public:
	InputManager();
	~InputManager();

	bool IsPressed(unsigned int keycode );
	bool IsReleased(unsigned int keycode);
	bool IsTriggered(unsigned int keycode);
	void Update();
private:
	Uint8 CurrentState[512];
	Uint8 PreviousState[512];
	
};
#endif

