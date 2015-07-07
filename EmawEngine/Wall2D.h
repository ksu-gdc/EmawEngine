//2D representation of wall
//Author: Ondrej Kuzela

#pragma once
#include "Collidable.h"
#include "MovingCollidable.h"

using namespace std;

class Wall2D : public Collidable{
private:
	float xa, ya, xb, yb;
public:
	Wall2D(float xa, float ya, float xb, float yb);

	// Computing collision with MovingCollidable
	bool collide(MovingCollidable * mc);
};