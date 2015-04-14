#pragma once
#include "GameObject.h"

class CollisionObject {

public:
	CollisionObject();
	CollisionObject(Vector*);
	CollisionObject(Vector*, float, float, float);
	~CollisionObject();

	void calculateCollisionBox(Vector*, std::vector<VERTEX>*, float, float, float);
	bool hasCollision(CollisionObject, float);

	float calculateRewindX();
	float calculateRewindY();
	float calculateRewindZ();

	Vector* _position;
	float lengthX;
	float lengthY;
	float lengthZ;

	GameObject* m_GameObject;


private:

	bool hasCollisionX(CollisionObject, float);
	bool hasCollisionY(CollisionObject, float);
	bool hasCollisionZ(CollisionObject, float);



};