#include "stdafx.h"
#include "MovingCollidable.h"
#include <cmath>

MovingCollidable::MovingCollidable(){

}

bool MovingCollidable::collide(MovingCollidable * mc){
	float x1 = getX();
	float y1 = getY();
	float z1 = getZ();

	float x2 = mc->getX();
	float y2 = mc->getY();
	float z2 = mc->getZ();

	float dist = getRadius() + mc->getRadius();

	if ((z1 > z2 && (z1 - getHeight()) < z2) || (z2 > z1 && (z2 - mc->getHeight()) < z1)){
		float x = x2 - x1;
		float y = y2 - y1;
		float dist2 = sqrt(x*x+y*y);
		if (dist2 < dist){
			pushBack();
			mc->pushBack();
			return true;
		}
	}
	return false;
}