/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:   Body

Purpose:
To implement body component of game object

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
#include "Body.h"
#include "Transform.h"
#include "CollisionManager.h"



Body::Body() : Component(BODY)
{
	mPosX = mPosY = 0;
	mPrevPosX = mPrevPosY = 0;
	mVelX = mVelY = 0;
	mAccX = mAccY = 0;
	mTotalForceX = mTotalForceY = 0;
	mMass = mInvMass = 0;
}


Body::~Body(){}

void Body::Update() { }

void Body::Serialize(FILE ** fpp)
{
	fscanf_s(*fpp, "%f\n", &mMass);
	if (0.0f != mMass) {
		mInvMass = 1.0f / mMass;
	}
	else {
		mInvMass = 0.0;
	}

	char bodytype[256];
	memset(bodytype, 0, 256 * sizeof(char));

	fscanf_s(*fpp, "%255s\n", bodytype, sizeof(bodytype));
	if (strcmp(bodytype, "Circle")==0)
	{
		mpShape = new ShapeCircle();
		mpShape->mpOwnerBody = this;
		ShapeCircle * pCircle = static_cast<ShapeCircle *> (mpShape);
		float radius;
		fscanf_s(*fpp, "%f\n", &radius);
		pCircle->mRadius = radius;
	}
	if (strcmp(bodytype, "AABB") == 0)
	{
		mpShape = new ShapeAABB();
		mpShape->mpOwnerBody = this;
		ShapeAABB * pAABB = static_cast<ShapeAABB *> (mpShape);
		float top, bot, left, right;
		fscanf_s(*fpp, "%f %f %f %f\n", &top, &bot, &left, &right);
		pAABB->mTop = top;
		pAABB->mBottom = bot;
		pAABB->mLeft = left;
		pAABB->mRight = right;
	}
}


void Body::Initialize()
{
	Transform * pTr = static_cast<Transform *> (mpOwner->getComponent(TRANSFORM));
	if (nullptr != pTr) 
	{
		mPrevPosX = mPosX = pTr->mxPos;
		mPrevPosY = mPosY = pTr->myPos;
	}
}

void Body::Integrate( float DeltaTime) 
{
	Transform * pTr = static_cast<Transform *> (mpOwner->getComponent(TRANSFORM));
	// Save Position
	mPrevPosX = mPosX;
	mPrevPosY = mPosY;

	// Calculate Acceleration
	
	mTotalForceY -= gravity;
	mAccX = mTotalForceX * mInvMass;
	mAccY = mTotalForceY * mInvMass;

	// Get velocity from acceleration - integration
	mVelX = mAccX * DeltaTime + mVelX;
	mVelY = mAccY * DeltaTime + mVelY;

	//Give position the velocity - integration
	mPosX = mVelX * DeltaTime + mPosX;
	mPosY = mVelY * DeltaTime + mPosY;


	mTotalForceX = mTotalForceY = 0.0f;

	if (nullptr != pTr)
	{
		pTr->mxPos = mPosX;
		pTr->myPos = mPosY;
	}
}

Component * Body::ReturnThis()
{
	Body * realbody = new Body(*this);

	realbody->mpShape = this->mpShape->ShapeVirtual();

	realbody->mpShape->mpOwnerBody = realbody;

	return realbody;
}
