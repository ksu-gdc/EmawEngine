#pragma once
#include "GameObject.h"

enum CollisionState{
	Fail,
	Succeed,
	Rewind,
};

class CollisionObject {

public:
	CollisionObject();
	~CollisionObject();

	void calculateCollisionBox(VERTEX*, std::vector<VERTEX>*);
	bool hasCollision(CollisionObject, float);

	float calculateRewindX();
	float calculateRewindY();
	float calculateRewindZ();

	VERTEX* center;
	float lengthX;
	float lengthY;
	float lengthZ;

	GameObject* m_GameObject;


private:

	bool hasCollisionX(CollisionObject, float);
	bool hasCollisionY(CollisionObject, float);
	bool hasCollisionZ(CollisionObject, float);



};