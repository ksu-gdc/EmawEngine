#include "stdafx.h"
#include "BoxCollidable.h"

BoxCollidable::BoxCollidable()
{
	width = 0;
	height = 0;
	length = 0;
}

BoxCollidable::BoxCollidable(float x, float y, float z)
{
	width = x;
	height = y;
	length = z;
}


BoxCollidable::~BoxCollidable()
{
}

void BoxCollidable::SetDimensions(float x, float y, float z)
{
	width = x;
	height = y;
	length = z;
}

void BoxCollidable::SetCurPos(Vector* v)
{
	curPos = v;
}

void BoxCollidable::SetLastPos(Vector* v)
{
	lastPos = v;
}

void BoxCollidable::pushBack()
{

}

void BoxCollidable::pushBack(float x, float y, float z)
{

}

Vector BoxCollidable::getDimensions()
{
	Vector packed;
	packed.x = width;
	packed.y = height;
	packed.z = length;
	return packed;
}

float BoxCollidable::getX()
{
	return curPos->x;
}

float BoxCollidable::getY()
{
	return curPos->y;
}

float BoxCollidable::getZ()
{
	return curPos->z;
}

float BoxCollidable::getLastX()
{
	return lastPos->x;
}

float BoxCollidable::getLastY()
{
	return lastPos->y;
}

float BoxCollidable::getLastZ()
{
	return lastPos->z;
}

float BoxCollidable::getRadius()
{
	return NULL;
}

float BoxCollidable::getHeight()
{
	return NULL;
}
