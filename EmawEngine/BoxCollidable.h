#pragma once

#include "stdafx.h"
class BoxCollidable : MovingCollidable
{
public:
	BoxCollidable();
	BoxCollidable(float, float, float);
	~BoxCollidable();
	
	void SetDimensions(float, float, float);
	void SetCurPos(Vector*);
	void SetLastPos(Vector*);
	Vector getDimensions();

	float getX();
	float getY();
	float getZ();

	float getLastX();
	float getLastY();
	float getLastZ();

	// Push back from collision to last position
	void pushBack();

	// Push back from collision to concrete position
	void pushBack(float, float, float);

	float getRadius();
	float getHeight();

private:
	float width;
	float height;
	float length;
	Vector* curPos;
	Vector* lastPos;
};

