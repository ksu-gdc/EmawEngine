#include "stdafx.h"
#include "Wall2D.h"


Wall2D::Wall2D(float x1, float y1, float x2, float y2){
	xa = x1;
	ya = y1;
	xb = x2;
	yb = y2;
}

// Computing collision with MovingCollidable
// Using Cramer's rule for equation solving
// http://en.wikipedia.org/wiki/Cramer%27s_rule
bool Wall2D::collide(MovingCollidable * mc){
	float x1, y1, x2, y2;

	//first get the current and last position of the object we're testing the wall against.
	x1 = mc->getX();
	y1 = mc->getZ();
	x2 = mc->getLastX();
	y2 = mc->getLastZ();

	//now we get the "rise and run" of the line between the two endpoints of the wall
	//so that we can describe the line in the form ax + by = c
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

	//now we get the "rise and run" for the line between the current and last positions
	//of the object that we're checking against so that we can describe the line in
	//the form ax + by = c
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

	//now that we've got the rises and runs for each line, we plug them into the formula
	//ax + by = c along with one of the endpoints for each line so that the formula is
	//-rise * endpointX + run * endpointY = c in order to get c (so we can then describe
	//the lines without needing a specific point on the line).
	float c1 = a1*xa + b1*ya;
	float c2 = a2*x1 + b2*y1;

	//Here we get the determinant to check to see if the lines actually intersect, if
	//the determinant is 0, then the lines are parallel or the same line and there can
	//be no intersection, so then there is no collision.
	float det = a1*b2 - b1*a2;
	if (det != 0) {

		//Here is where we use Cramer's rule to get the x and y coordinates that
		//both lines pass through.  This is where the lines intersect and where
		//the collision will have taken place.
		float x = (c1*b2 - b1*c2) / det;
		float y = (a1*c2 - c1*a2) / det;

		//Here we get the radius of the colliding object and check to see if
		//the current position of the object is close enough to the intersect
		//point that a collision occurs.  We also check to see that the object
		//has not passed through the wall between frames.
		//NOTE: This method of collision detection will fail if the colliding object
		//is moving vertically along the Y-axis (well, technically it's the Z-axis but
		//within this method we're treating it as the Y-axis) and passes through the 
		//wall entirely between frames.
		float radius = mc->getRadius();
		float tempX = x1 - x;
		float tempY = y1 - y;
		float dist = sqrt(tempX*tempX + tempY*tempY);
		if (dist < radius || (x1<x && x<x2) || (x1>x && x>x2)){
			float newX;
			if (x > x2){
				newX = x2 - 0.0002f;
			}
			else {
				newX = x2 + 0.0002f;
			}
			float newZ = (c2 - a2*newX) / b2;

			mc->pushBack(newX, mc->getLastY(), newZ);
			return true;
		}
	}
	return false;
}