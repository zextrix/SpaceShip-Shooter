/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    Timer

Purpose:
Controls frame rate of the application

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
#include "Timer.h"
#include "SDL_timer.h"

Timer::Timer(Uint32 MaxFrameRate) {
	mTickStart = mTickEnd = mFrameTime = 0;

	if (0 != MaxFrameRate)
		mNeededTicksPerFrame = 1000 / MaxFrameRate;
	else
		mNeededTicksPerFrame = 0;
}

Timer::~Timer() {
}

void Timer::FrameStart() {
	mTickStart = SDL_GetTicks();
}

void Timer::FrameEnd() {
	mTickEnd = SDL_GetTicks();
	while ((mTickEnd - mTickStart < mNeededTicksPerFrame))
		mTickEnd = SDL_GetTicks();

	mFrameTime = mTickEnd - mTickStart;
}

Uint32 Timer::GetFrameTime() {
	Uint32 x;
	if (mFrameTime == 0)
		x = 0;
	else
		x = 1000/mFrameTime;
	return x;
}