#include "stdafx.h"
#include "Wall2D.h"


Wall2D::Wall2D(float x1, float y1, float x2, float y2){
	xa = x1;
	ya = y1;
	xb = x2;
	yb = y2;
}
bool Wall2D::collide(MovingCollidable * mc, bool xy){
	int x1, y1, x2, y2;
	if (xy){
		x1 = mc->getX();
		y1 = mc->getY();
		x2 = mc->getLastX();
		y2 = mc->getLastY();
	}
	else {
		x1 = mc->getY();
		y1 = mc->getZ();
		x2 = mc->getLastY();
		y2 = mc->getLastZ();
	}

	//collision
}