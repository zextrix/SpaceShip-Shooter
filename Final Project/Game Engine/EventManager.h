/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    EventManager

Purpose:
To manage timed events

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
#include <list>
#include <unordered_map>
class GameObject;
enum EventType
{
	SPEED_UP,
	S_ACTIVE,
	TRI_BUL,
	T_ACTIVE,
	NUM
};

class Event
{
public:
	Event(EventType);
	virtual ~Event() {}
public:
	EventType mType;
	float mTimer;
};

class EventManager 
{
public:
	EventManager();
	~EventManager();
	void BroadcastEvent(Event * pEvent);
	void AddTimedEvent(Event * pEvent);
	void Update(float frameTime);
	void Subscribe(EventType Type, GameObject * pgameObject);
	void BroadcastEventToSubscribe(Event *pEvent);
	void UnSubscirbe(EventType Type, GameObject *pGameObjectOldSubscribe);
public:
	std::list<Event *>mTimedEvents;
	std::unordered_map<EventType, std::list<GameObject *>> mSubscriptions;

};
