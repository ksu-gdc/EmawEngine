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

	if ((y1 > y2 && (y1 - getHeight()) < y2) || (y2 > y1 && (y2 - mc->getHeight()) < y1)){
		float x = x2 - x1;
		float z = z2 - z1;
		float dist2 = sqrt(x*x+z*z);
		if (dist2 < dist){
			pushBack();
			mc->pushBack();
			return true;
		}
	}
	return false;
}