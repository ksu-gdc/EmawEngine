#include "stdafx.h"
#include "CollisionManager.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool CollisionManager::instanceFlag = false;
CollisionManager* CollisionManager::instance = NULL;

CollisionManager::CollisionManager(){
	xzCounter = 0;
	xzWalls = NULL;
	level = -1;
	floor = 1;
	ceiling = -1;
}


CollisionManager::~CollisionManager(){
	for (int i = 0; i < xzCounter; i++){
		delete xzWalls[i];
	}
	delete[] xzWalls;

	list<MovingCollidable*>::iterator i;
	for (i = movingCollidables.begin(); i != movingCollidables.end(); ++i){
		delete *i;
	}
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

// Adding moving collidable
void CollisionManager::addMovingCollidable(MovingCollidable* mc){
	movingCollidables.push_back(mc);
}

// Removing moving collidable
void CollisionManager::removeMovingCollidable(MovingCollidable* mc){
	movingCollidables.remove(mc);
}

// Checking of collisions for single moving collidable
// Collisions between moving collidables are skipped
bool CollisionManager::checkCollisions(){
	return checkXZCollisions() || checkYCollisions();
}

// Checking of collisions for all moving collidables
// Collisions between moving collidables are skipped
bool CollisionManager::checkCollisions(MovingCollidable* mc){
	return checkXZCollisions(mc) || checkYCollisions(mc);
}

// Checking of wall collisions for single moving collidable
bool CollisionManager::checkXZCollisions(MovingCollidable* mc){
	for (int j = 0; j < xzCounter; j++){
		if (xzWalls[j]->collide(mc)){
			return true;
		}
	}
	return false;
}

// Checking of wall collisions for all moving collidables
bool CollisionManager::checkXZCollisions(){
	bool res = false;
	list<MovingCollidable*>::iterator i;
	for (i = movingCollidables.begin(); i != movingCollidables.end(); ++i){
		if (checkXZCollisions(*i)){
			res = true;
		}
	}
	return res;
}

// Checking of floor/ceiling collisions for single moving collidable
bool CollisionManager::checkYCollisions(MovingCollidable* mc){
	if (mc->getY() >= ceiling){
		mc->pushBack(mc->getX(), mc->getLastY()-0.0001f, mc->getZ());
		return true;
	}
	if ((mc->getY() - mc->getHeight()) <= floor){
		mc->pushBack(mc->getX(), mc->getLastY() + 0.0001f, mc->getZ());
		return true;
	}
	return false;
}

// Checking of floor/ceiling collisions for all moving collidables
bool CollisionManager::checkYCollisions(){
	bool res = false;
	list<MovingCollidable*>::iterator i;
	for (i = movingCollidables.begin(); i != movingCollidables.end(); ++i){
		if (checkYCollisions(*i)){
			res = true;
		}
	}
	return res;
}

// Checking of collisions between moving collidables
bool CollisionManager::checkMovingCollisions(){
	while (checkMovingCollisionsInner());
	return false;
}

// Checking collisions between moving collidables, supporting inner function
bool CollisionManager::checkMovingCollisionsInner(){
	bool res = false;
	list<MovingCollidable*>::iterator i;
	list<MovingCollidable*>::iterator j;
	for (i = movingCollidables.begin(); i != movingCollidables.end(); ++i){
		for (j = ++i; j != movingCollidables.end(); ++j){
			res = res || ((*i)->collide(*j));
		}
	}
	return res;
}

// Loading of static collision setting for level
void CollisionManager::loadLevel(int id){
	float a, b, c, d;

	level = id;

	fstream xzfile("collision/level" + to_string(id) + ".txt", ios_base::in);
	if (xzfile.is_open()){
		for (int i = 0; i < xzCounter; i++){
			delete xzWalls[i];
		}
		delete[] xzWalls;
		
		xzfile >> ceiling;
		xzfile >> floor;
		xzfile >> xzCounter;

		xzWalls = new Wall2D*[xzCounter];
		for (int i = 0; i < xzCounter; i++){
			xzfile >> a;
			xzfile >> b;
			xzfile >> c;
			xzfile >> d;
			xzWalls[i] = new Wall2D(a, b, c, d);
		}
		xzfile.close();
	}
}