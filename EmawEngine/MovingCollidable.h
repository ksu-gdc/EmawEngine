//Collidable that can move
//Author: Ondrej Kuzela

#pragma once
#include "Collidable.h"

using namespace std;

class MovingCollidable : public Collidable{
public:
	virtual float getX();
	virtual float getY();
	virtual float getZ();

	virtual float getLastX();
	virtual float getLastY();
	virtual float getLastZ();

	virtual void pushBack();

	bool collide(MovingCollidable * mc);

	virtual float getRadius();
	virtual float getHeight();
};