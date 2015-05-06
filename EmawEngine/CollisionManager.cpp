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

void CollisionManager::addMovingCollidable(MovingCollidable* mc){
	movingCollidables.push_back(mc);
}

void CollisionManager::removeMovingCollidable(MovingCollidable* mc){
	movingCollidables.remove(mc);
}

bool CollisionManager::checkCollisions(){
	return checkXZCollisions() || checkYCollisions();
}

bool CollisionManager::checkCollisions(MovingCollidable* mc){
	return checkXZCollisions(mc) || checkYCollisions(mc);
}

bool CollisionManager::checkXZCollisions(MovingCollidable* mc){
	for (int j = 0; j < xzCounter; j++){
		if (xzWalls[j]->collide(mc)){
			return true;
		}
	}
	return false;
}

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

bool CollisionManager::checkMovingCollisions(){
	while (checkMovingCollisionsInner());
	return false;
}

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

void CollisionManager::loadLevel(int id){
	float a, b, c, d;

	level = id;

	fstream xzfile("collision/level" + to_string(id) + ".txt", ios_base::in);
	if (xzfile.is_open()){
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