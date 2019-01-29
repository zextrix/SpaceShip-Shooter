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
#ifndef  TIMER_H
#define  TIMER_H
#include <SDL_stdinc.h>
class Timer {
public:
	Timer(Uint32 MaxFrameRate);
	~Timer();

	void FrameStart();
	void FrameEnd();
	Uint32 GetFrameTime();
private:
	Uint32 mTickStart;
	Uint32 mTickEnd;
	Uint32 mFrameTime;
	Uint32 mNeededTicksPerFrame;
};
#endif 
