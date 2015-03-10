//Class for Position
//Author: Ondrej Kuzela
#pragma once
#include "SFX.h"

class Position{
private:
	float x;
	float y;
	float z;
public:
	Position();
	Position(Position* p);
	Position(float tX, float tY, float tZ);
	void setX(float nX);
	void setY(float nY);
	void setZ(float nZ);
	float getX();
	float getY();
	float getZ();
	FMOD_VECTOR getVector();
	bool isEmpty();
};