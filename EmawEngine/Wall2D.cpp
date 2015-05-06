#include "stdafx.h"
#include "Wall2D.h"


Wall2D::Wall2D(float x1, float y1, float x2, float y2){
	xa = x1;
	ya = y1;
	xb = x2;
	yb = y2;
}

// Using Cramer's rule for equation solving
// http://en.wikipedia.org/wiki/Cramer%27s_rule
bool Wall2D::collide(MovingCollidable * mc){
	float x1, y1, x2, y2;

	x1 = mc->getX();
	y1 = mc->getZ();
	x2 = mc->getLastX();
	y2 = mc->getLastZ();

	float a1 = xb - xa;
	float b1 = yb - ya;
	if (b1 < 0){
		float temp = a1;
		a1 = -b1;
		b1 = temp;
	}
	else {
		float temp = a1;
		a1 = b1;
		b1 = -temp;
	}

	float a2 = x2 - x1;
	float b2 = y2 - y1;
	if (b2 < 0){
		float temp = a2;
		a2 = -b2;
		b2 = temp;
	}
	else {
		float temp = a2;
		a2 = b2;
		b2 = -temp;
	}

	float c1 = a1*xa + b1*ya;
	float c2 = a2*x1 + b2*y1;

	float det = a1*b2 - b1*a2;
	if (det != 0) {
		float x = (c1*b2 - b1*c2) / det;
		float y = (a1*c2 - c1*a2) / det;

		float radius = mc->getRadius();
		float tempX = x1 - x;
		float tempY = y1 - y;
		float dist = sqrt(tempX*tempX + tempY*tempY);
		if (dist < radius || (x1<x && x<x2) || (x1>x && x>x2)){
			float newX;
			if (x > x2){
				newX = x2 - 0.0001f;
			}
			else {
				newX = x2 + 0.0001f;
			}
			float newZ = (c2-a2*newX) / b2;
			
			mc->pushBack(newX, mc->getLastY(), newZ);
			return true;
		}
	}
	return false;
}