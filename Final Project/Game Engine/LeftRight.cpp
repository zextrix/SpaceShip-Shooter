#include "LeftRight.h"
#include "Timer.h"
#include "Body.h"
#include "Transform.h"

extern Timer *gpTime;

LeftRight::LeftRight() : Component(LEFTRIGHT)
{
	mGoingRight = true;
	mTimer = 0;
	mTimerLimit = 1000;
}


LeftRight::~LeftRight()
{
}

void LeftRight::Update() {
	mTimer += gpTime->GetFrameTime()/2;
	if (mTimer > mTimerLimit) {
		mGoingRight = !mGoingRight;
		mTimer = 0;
	}
	Body * pBody = static_cast<Body *> (mpOwner->getComponent(BODY));
	Transform * pTrs = static_cast<Transform *> (mpOwner->getComponent(TRANSFORM));

	if (mGoingRight)
	{
		pBody->mPosX += mSpeed;
	}
	else
	{
		pBody->mPosX -= mSpeed;
	}
}

void LeftRight::Serialize(FILE **fpp) 
{
	int goingRight, timerLimit;
	float spd;
	fscanf_s(*fpp, "%i %i %f\n", &goingRight, &timerLimit, &spd);
	mGoingRight = (bool)goingRight;
	mTimerLimit = timerLimit;
	mSpeed = spd;
}

void LeftRight::HandleEvent(Event * pEvent)
{
}

Component * LeftRight::ReturnThis()
{
	return new LeftRight(*this);
}