//Collision Manager
//Author: Ondrej Kuzela

#include "stdafx.h"
#include <cstdlib>
#include "CollisionManager.h"

using namespace std;

bool CollisionManager::instanceFlag = false;
CollisionManager* CollisionManager::instance = NULL;

CollisionManager::CollisionManager() {
}

// Returns the instance of our CollisionManager
CollisionManager* CollisionManager::getInstance() {
	if (!instanceFlag)
	{
		instance = new CollisionManager();
		instanceFlag = true;
	}
	return instance;
}

bool CollisionManager::collide(){
	return staticCollider.checkCollisions(dynamicColliders);
}


bool CollisionManager::collide(Collidable c){
	return staticCollider.checkCollisions(c);
}