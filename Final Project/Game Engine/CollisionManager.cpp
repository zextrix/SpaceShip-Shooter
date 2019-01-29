/*------------------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    Component

Purpose:
To implement component based architecture

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
#include "CollisionManager.h"
#include "Body.h"

Shape::Shape(ShapeType Type)
{
	mType = Type;
	mpOwnerBody = nullptr;
}

ShapeCircle::ShapeCircle() : Shape(CIRCLE) {
}

ShapeCircle::~ShapeCircle() {
}

bool ShapeCircle::TestPoint(float PointX, float PointY) {
	return false;
}


ShapeAABB::ShapeAABB() : Shape(RECTANGLE) {
}

ShapeAABB::~ShapeAABB() {

}

bool ShapeAABB::TestPoint(float PointX, float PointY) {
	return false;
}

Contact::Contact() {
	mpBodies[0] = nullptr;
	mpBodies[1] = nullptr;
}


bool CheckCollisionCircleToCircle(Shape *pShape1, float Pos1X, float Pos1Y,
	Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact  *> &Contacts) {

	//Intersect
	ShapeCircle * c1 = static_cast<ShapeCircle *>(pShape1);
	ShapeCircle * c2 = static_cast<ShapeCircle *>(pShape2);

	if (1) {
		return false;
	}

	//Create contact
	Contact *pNewContact = new Contact();
	pNewContact->mpBodies[0] = pShape1->mpOwnerBody;
	pNewContact->mpBodies[1] = pShape2->mpOwnerBody;
	Contacts.push_back(pNewContact);
	return true;
}

bool CheckCollisionCircleToAABB(Shape *pShape1, float Pos1X, float Pos1Y,
	Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact  *> &Contacts) {
	return true;
}

bool CheckCollisionAABBToAABB(Shape *pShape1, float Pos1X, float Pos1Y,
	Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact  *> &Contacts) {


	ShapeAABB * r1 = static_cast<ShapeAABB *>(pShape1);
	ShapeAABB * r2 = static_cast<ShapeAABB *>(pShape2);

	

	if ((Pos1X + r1->mBottom/2.0f ) < (Pos2X - r2->mBottom / 2.0f) ||
		(Pos1X - r1->mBottom/2.0f ) > (Pos2X + r2->mBottom / 2.0f) ||
		(Pos1Y + r1->mLeft/2.0f  ) < (Pos2Y - r2->mLeft / 2.0f) ||
		(Pos1Y - r1->mLeft/2.0f ) > (Pos2Y + r2->mLeft / 2.0f)) {
		return false;
	}

	//Create a new contact and add it
	Contact *pNewContact = new Contact();
	pNewContact->mpBodies[0] = pShape1->mpOwnerBody;
	pNewContact->mpBodies[1] = pShape2->mpOwnerBody;
	
	/*float Pos1X2 = Pos1X + r1->mBottom;
	float Pos1Y2 = Pos1Y + r1->mLeft;

	float Pos2X2 = Pos2X + r2->mBottom;
	float Pos2Y2 = Pos2Y + r2->mLeft;
		
	float x_overlap = abs(Pos1X - Pos2X) - abs(Pos1X2 - Pos2X2);
	float y_overlap = abs(Pos1Y - Pos2Y) - abs(Pos1Y2 - Pos2Y2);
*/

	float pS1width_extent = r1->mBottom * 0.5f;
	float pS1height_extent = r1->mLeft * 0.5f;

	float pS2width_extent = r2->mBottom * 0.5f;
	float pS2height_extent = r2->mLeft * 0.5f;

	float pS1x = Pos1X; //+ pS1width_extent;
	float pS1y = Pos1Y; //+ pS1height_extent;
	float pS2x = Pos2X; //+ pS2width_extent;
	float pS2y = Pos2Y; //+ pS2height_extent;
					   //
	float tempNormalx = pS1x - pS2x;
	float tempNormaly = pS1y - pS2y;
	
	float x_overlap = pS1width_extent + pS2width_extent - abs(tempNormalx);
	float y_overlap = pS1height_extent + pS2height_extent - abs(tempNormaly);
	
	
	if (x_overlap < y_overlap) {
		if (tempNormalx < 0)
			pNewContact->n = { 1.0f, 0.0f };
		else
			pNewContact->n = { -1.0f, 0.0f };
		
		pNewContact->pen = x_overlap ;
	}
	else {
		if (tempNormaly < 0)
			pNewContact->n = { 0.0f, 1.0f };
		else
			pNewContact->n = { 0.0f, -1.0f };
		
		pNewContact->pen = y_overlap ;
	}


	Contacts.push_back(pNewContact);
	return true;
}

CollisionManager::CollisionManager() {
	CollisionFunctions[Shape::CIRCLE][Shape::CIRCLE] = CheckCollisionCircleToCircle;
	CollisionFunctions[Shape::CIRCLE][Shape::RECTANGLE] = CheckCollisionCircleToAABB;
	CollisionFunctions[Shape::RECTANGLE][Shape::CIRCLE] = CheckCollisionCircleToAABB;
	CollisionFunctions[Shape::RECTANGLE][Shape::RECTANGLE] = CheckCollisionAABBToAABB;
}


CollisionManager::~CollisionManager() {
}


void CollisionManager::Reset() {
	for (auto c : mContacts) {
		delete c;
	}
	mContacts.clear();
}

bool CollisionManager::CheckCollisionAndGenerateContact(Shape *pShape1, float Pos1X, float Pos1Y,
	Shape *pShape2, float Pos2X, float Pos2Y) {
	return CollisionFunctions[pShape1->mType][pShape2->mType](pShape1, Pos1X, Pos1Y,
		pShape2, Pos2X, Pos2Y, mContacts);
}

void Contact::Impulser() 
{
	Body * b1 = mpBodies[0];
	Body * b2 = mpBodies[1];

	float rel;
	glm::vec2 impulse;
	glm::vec2 magimpulse;

	glm::vec2 relative(b2->mVelX - b1->mVelX, b2->mVelY - b1->mVelY);

	rel = glm::dot(relative, n);

	float e = 0.0f;
	float j = -(1 + e) * rel;

	if (b1->mInvMass != 0 || b2->mInvMass != 0)
		j /= b1->mInvMass + b2->mInvMass;

	
	impulse.x = n.x * j;
	impulse.y = n.y * j;

	magimpulse.x = impulse.x * b1->mInvMass;
	magimpulse.y = impulse.y * b1->mInvMass;
	b1->mVelX = b1->mVelX - magimpulse.x;
	b1->mVelY = b1->mVelY - magimpulse.y;

	magimpulse.x = impulse.x * b2->mInvMass;
	magimpulse.y = impulse.y * b2->mInvMass;
	b2->mVelX = b2->mVelX + magimpulse.x;
	b2->mVelY = b2->mVelY + magimpulse.y;
}

void Contact::Correction() 
{
	Body * b1 = mpBodies[0];
	Body * b2 = mpBodies[1];

	glm::vec2 correctit;
	glm::vec2 mag_correct;
	correctit.x = n.x * pen;
	correctit.y = n.y * pen;


	mag_correct.x = correctit.x * b1->mInvMass;
	mag_correct.y = correctit.y * b1->mInvMass;
	b1->mPosX = b1->mPosX - mag_correct.x;
	b1->mPosY = b1->mPosY - mag_correct.y;

	mag_correct.x = correctit.x * b2->mInvMass;
	mag_correct.y = correctit.y * b2->mInvMass;
	b2->mPosX = b2->mPosX + mag_correct.x;
	b2->mPosY = b2->mPosY + mag_correct.y;
}

