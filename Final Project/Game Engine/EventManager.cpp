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
#include "EventManager.h"
#include "GameObjectManager.h"
#include "Body.h"

extern GameObjectManager *gpGOM;

Event::Event(EventType type)
{
	mTimer = 5.00f;
	mType = type;
}



EventManager::EventManager() {}

EventManager::~EventManager() {}

void EventManager::BroadcastEvent(Event * pEvent) 
{
	for (auto go : gpGOM->LGameObject)
		go->HandleEvent(pEvent);
}

void EventManager::AddTimedEvent(Event * pEvent)
{
	mTimedEvents.push_back(pEvent);
}

void EventManager::Update(float frameTime)
{
	//Loop Through all time events
	//Decrease timer by Frametime
	// < 0 ? -> fire event, Remove from list
	std::list <Event*>::iterator it, itTemp, itEnd;

	itEnd = mTimedEvents.end();
	it = mTimedEvents.begin();

	while (it != mTimedEvents.end())
	{
		Event * pEvent = *it;
		pEvent->mTimer -= frameTime;
		if (pEvent->mTimer < 0.0f)
		{
			BroadcastEvent(pEvent);
			it = mTimedEvents.erase(it);
			delete pEvent;
		}
		else
		{
			++it;
		}
	}
}

void EventManager::Subscribe(EventType Type, GameObject * pGameObjectNewSubscriber)
{
	//std::list <GameObject*> &istOfsubscribers = mSubscriptions[Type];
	auto &listOfsubscribers = mSubscriptions[Type];

	for (auto pGo : listOfsubscribers)
		if (pGo == pGameObjectNewSubscriber)
			return;

	listOfsubscribers.push_back(pGameObjectNewSubscriber);
}

void EventManager::BroadcastEventToSubscribe(Event * pEvent)
{
	auto &istOfsubscribers = mSubscriptions[pEvent->mType];
	for (auto pGo : istOfsubscribers)
		pGo->HandleEvent(pEvent);
}

void EventManager::UnSubscirbe(EventType Type, GameObject *pGameObjectOldSubscribe)
{
	auto &listOfSubscribers = mSubscriptions[Type];

	auto it = std::find(listOfSubscribers.begin(),
		listOfSubscribers.end(),
		pGameObjectOldSubscribe);

	if (it == listOfSubscribers.end())
		return;

	listOfSubscribers.erase(it);
}