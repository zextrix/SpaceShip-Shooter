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
#pragma once
#include <list>
#include <glm/glm.hpp>
class Body;
class Shape
{
public:
	enum ShapeType {
		CIRCLE,
		RECTANGLE,

		NUM
	};
	Shape(ShapeType Type);
	virtual ~Shape() {}
	virtual bool TestPoint(float PointX, float PointY) = 0;
	virtual Shape * ShapeVirtual() = 0;
public:
	Body * mpOwnerBody;
	ShapeType mType;
};

// ---------------------------------

class ShapeCircle : public Shape {
public:
	ShapeCircle();
	~ShapeCircle();
	bool TestPoint(float PointX, float PointY);
	virtual Shape * ShapeVirtual()
	{
		return new ShapeCircle(*this);
	}
public:
	float mRadius;
};

// --------------------------------

class ShapeAABB : public Shape {
public:
	ShapeAABB();
	~ShapeAABB();
	bool TestPoint(float PointX, float PointY);
	virtual Shape * ShapeVirtual()
	{
		return new ShapeAABB(*this);
	}
public:
	float mTop, mBottom, mRight, mLeft;
};

// ------------------------------

class Contact {
public:
	Contact();
	~Contact() {}
	void Impulser();
	void Correction();
public:
	Body *mpBodies[2];
	glm::vec2 n;
	float pen;
};

// ---------------------------------

class CollisionManager {
public:
	CollisionManager();
	~CollisionManager();
	void Reset();
	bool CheckCollisionAndGenerateContact(Shape *pShape1, float Pos1X, float Pos1Y,
		Shape *pShape2, float Pos2X, float Pos2Y);
public:
	std::list<Contact *> mContacts;
private:
	//2D array of function pointers, used to store the collison function addresses
	bool(*CollisionFunctions[Shape::NUM][Shape::NUM]) (Shape *pShape1, float Pos1X, float Pos1Y,
		Shape *pShape2, float Pos2X, float Pos2Y,
		std::list<Contact  *> &Contacts);

};