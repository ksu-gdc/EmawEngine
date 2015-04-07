#include "stdafx.h"
#include "CollisionObject.h"

CollisionObject::CollisionObject() {
	lengthX = 0;
	lengthY = 0;
	lengthZ = 0;
	center = new VERTEX();
}

CollisionObject::~CollisionObject() {}

void CollisionObject::calculateCollisionBox(VERTEX* c, std::vector<VERTEX>* verticies){

	center = c;

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

	lengthX = lengthX * *m_GameObject->_scale->x;
	lengthY = lengthY * *m_GameObject->_scale->y;
	lengthZ = lengthZ * *m_GameObject->_scale->z;

}

/*bool CollisionObject::hasCollisionX(CollisionObject b){

	float xminA = center->X - (lengthX / 2);
	float xmaxA = center->X + (lengthX / 2);
	float xminB = b.center->X - (b.lengthX / 2);
	float xmaxB = b.center->X + (b.lengthX / 2);

	if (xminA < xmaxB && xmaxA > xminB) return true;

	return false;
}

bool CollisionObject::hasCollisionY(CollisionObject b){

	float yminA = center->Y - (lengthY / 2);
	float ymaxA = center->Y + (lengthY / 2);
	float yminB = b.center->Y - (b.lengthY / 2);
	float ymaxB = b.center->Y + (b.lengthY / 2);

	if (yminA < ymaxB && ymaxA > yminB) return true;

	return false;
}

bool CollisionObject::hasCollisionZ(CollisionObject b){

	float zminA = center->Z - (lengthZ / 2);
	float zmaxA = center->Z + (lengthZ / 2);
	float zminB = b.center->Z - (b.lengthZ / 2);
	float zmaxB = b.center->Z + (b.lengthZ / 2);

	if (zminA < zmaxB && zmaxA > zminB) return true;

	return false;
}*/

bool CollisionObject::hasCollision(CollisionObject b, float gameTime){

	if (hasCollisionX(b, gameTime) && hasCollisionY(b, gameTime) && hasCollisionZ(b, gameTime)){
		m_GameObject->m_HasCollision = true;
	}

	return false;
}

bool CollisionObject::hasCollisionX(CollisionObject b, float gameTime){

	float newCenterA = center->X + *m_GameObject->_velocity->x * gameTime;
	float newCenterB = b.center->X + *b.m_GameObject->_velocity->x * gameTime;

	float xminA = newCenterA - (lengthX / 2);
	float xmaxA = newCenterA + (lengthX / 2);
	float xminB = newCenterB - (b.lengthX / 2);
	float xmaxB = newCenterB + (b.lengthX / 2);

	if (xminA < xmaxB && xmaxA > xminB) return true;

	return false;
}

bool CollisionObject::hasCollisionY(CollisionObject b, float gameTime){

	float newCenterA = center->Y + *m_GameObject->_velocity->y * gameTime;
	float newCenterB = b.center->Y + *b.m_GameObject->_velocity->y * gameTime;

	float yminA = newCenterA - (lengthY / 2);
	float ymaxA = newCenterA + (lengthY / 2);
	float yminB = newCenterB - (b.lengthY / 2);
	float ymaxB = newCenterB + (b.lengthY / 2);

	if (yminA < ymaxB && ymaxA > yminB) return true;

	return false;
}

bool CollisionObject::hasCollisionZ(CollisionObject b, float gameTime){

	float newCenterA = center->Z + *m_GameObject->_velocity->z * gameTime;
	float newCenterB = b.center->Z + *b.m_GameObject->_velocity->z * gameTime;

	float zminA = newCenterA - (lengthZ / 2);
	float zmaxA = newCenterA + (lengthZ / 2);
	float zminB = newCenterB - (b.lengthZ / 2);
	float zmaxB = newCenterB + (b.lengthZ / 2);

	if (zminA < zmaxB && zmaxA > zminB) return true;

	return false;
}