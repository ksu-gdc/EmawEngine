//Collidable that can move
//Author: Ondrej Kuzela

#pragma once
#include "Collidable.h"

using namespace std;

class MovingCollidable : public Collidable{
protected:
	MovingCollidable();
public:
	virtual float getX() = 0;
	virtual float getY() = 0;
	virtual float getZ() = 0;

	virtual float getLastX() = 0;
	virtual float getLastY() = 0;
	virtual float getLastZ() = 0;

	virtual void pushBack() = 0;
	virtual void pushBack(float x, float y, float z) = 0;

	bool collide(MovingCollidable * mc);

	virtual float getRadius() = 0;
	virtual float getHeight() = 0;

};