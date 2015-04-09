//Collision Manager
//Author: Ondrej Kuzela

#pragma once
#include <string>
#include <list>
#include "Collidable.h"
#include "StaticCollider.h"

using namespace std;

class CollisionManager {
private:
	CollisionManager();

	// Statics
	static bool instanceFlag;
	static CollisionManager *instance;

	
	list<Collidable> dynamicColliders;
	StaticCollider staticCollider;

public:
	~CollisionManager();

	// Singleton accessor
	static CollisionManager* getInstance();

	bool collide();
	bool collide(Collidable c);
};