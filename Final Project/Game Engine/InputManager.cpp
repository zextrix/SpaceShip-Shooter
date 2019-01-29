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
#include "InputManager.h"



InputManager::InputManager()
{
	SDL_memset(CurrentState, 0, 512 * sizeof(Uint8));
	SDL_memset(PreviousState, 0, 512 * sizeof(Uint8));
}


InputManager::~InputManager()
{
}

bool InputManager::IsPressed(unsigned int keycode)
{
	if (keycode >= 512)
		return false;
	if (CurrentState[keycode])
	{
		return true;
	}
	return false;
}

bool InputManager::IsReleased(unsigned int keycode)
{
	if (keycode >= 512)
		return false;
	if (!CurrentState[keycode] && PreviousState[keycode])
		return true;
	return false;
}

bool InputManager::IsTriggered(unsigned int keycode)
{
	if (keycode >= 512)
		return false;
	if (CurrentState[keycode] && !PreviousState[keycode])
		return true;
	return false;
}

void InputManager::Update()
{
	int fetchedkey = 0;
	const Uint8 *CurrentKeyPress = SDL_GetKeyboardState(&fetchedkey);
	if (fetchedkey > 512)
	{
		fetchedkey = 512;
	}
	SDL_memcpy(PreviousState, CurrentState, 512 * sizeof(Uint8));
	SDL_memcpy(CurrentState, CurrentKeyPress, fetchedkey * sizeof(Uint8));
}
