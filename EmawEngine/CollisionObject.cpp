#include "stdafx.h"
#include "CollisionObject.h"

CollisionObject::CollisionObject() {
	lengthX = 0;
	lengthY = 0;
	lengthZ = 0;
	_position = new Vector();
}

CollisionObject::CollisionObject(Vector* pos) {
	lengthX = 0;
	lengthY = 0;
	lengthZ = 0;
	_position = pos;
}

CollisionObject::CollisionObject(Vector* pos, float x, float y, float z) {
	lengthX = x;
	lengthY = y;
	lengthZ = z;
	_position = pos;
}

CollisionObject::~CollisionObject() {}

void CollisionObject::calculateCollisionBox(Vector* c, std::vector<VERTEX>* verticies, float sx, float sy, float sz){

	_position = c;

	for (int i = 0; i < verticies->size(); i++){

		for (int j = i + 1; j < verticies->size(); j++){

			if (abs(verticies->at(i).X - verticies->at(j).X) > lengthX){
				lengthX = abs(verticies->at(i).X - verticies->at(j).X);
			}
			if (abs(verticies->at(i).Y - verticies->at(j).Y) > lengthY){
				lengthY = abs(verticies->at(i).Y - verticies->at(j).Y);
			}
			if (abs(verticies->at(i).Z - verticies->at(j).Z) > lengthZ){
				lengthZ = abs(verticies->at(i).Z - verticies->at(j).Z);
			}
		}
	}

	lengthX = lengthX * sx;
	lengthY = lengthY * sy;
	lengthZ = lengthZ * sz;

}

bool CollisionObject::hasCollision(CollisionObject b, float gameTime){

	if (hasCollisionX(b, gameTime) && hasCollisionY(b, gameTime) && hasCollisionZ(b, gameTime)){
		m_GameObject->setCollision(true);
	}

	return false;
}

bool CollisionObject::hasCollisionX(CollisionObject b, float gameTime){

	float newCenterA = _position->x;
	float newCenterB = b._position->x;

	float xminA = newCenterA - (lengthX / 2);
	float xmaxA = newCenterA + (lengthX / 2);
	float xminB = newCenterB - (b.lengthX / 2);
	float xmaxB = newCenterB + (b.lengthX / 2);

	if (xminA < xmaxB && xmaxA > xminB) return true;

	return false;
}

bool CollisionObject::hasCollisionY(CollisionObject b, float gameTime){

	float newCenterA = _position->y;
	float newCenterB = b._position->y;

	float yminA = newCenterA - (lengthY / 2);
	float ymaxA = newCenterA + (lengthY / 2);
	float yminB = newCenterB - (b.lengthY / 2);
	float ymaxB = newCenterB + (b.lengthY / 2);

	if (yminA < ymaxB && ymaxA > yminB) return true;

	return false;
}

bool CollisionObject::hasCollisionZ(CollisionObject b, float gameTime){

	float newCenterA = _position->z;
	float newCenterB = b._position->z;

	float zminA = newCenterA - (lengthZ / 2);
	float zmaxA = newCenterA + (lengthZ / 2);
	float zminB = newCenterB - (b.lengthZ / 2);
	float zmaxB = newCenterB + (b.lengthZ / 2);

	if (zminA < zmaxB && zmaxA > zminB) return true;

	return false;
}