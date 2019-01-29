#pragma once
#include "Component.h"
class LeftRight : public Component
{
public:
	LeftRight();
	~LeftRight();
	void Update();
	void Serialize(FILE **fpp);
	void HandleEvent(Event * pEvent);
	Component * ReturnThis();
	bool mGoingRight;
	int mTimer, mTimerLimit;
	float mSpeed;
};

