#include "stdafx.h"
#include "CollisionManager.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool CollisionManager::instanceFlag = false;
CollisionManager* CollisionManager::instance = NULL;

CollisionManager::CollisionManager(){
	xyCounter = 0;
	yzCounter = 0;
	xyWalls = NULL;
	yzWalls = NULL;
}


CollisionManager::~CollisionManager(){
	for (int i = 0; i < xyCounter; i++){
		delete xyWalls[i];
	}
	delete[] xyWalls;

	for (int i = 0; i < yzCounter; i++){
		delete yzWalls[i];
	}
	delete[] yzWalls;

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
	return checkXYCollisions() || checkYZCollisions() || checkMovingCollisions();
}

bool CollisionManager::checkXYCollisions(){
	bool res = false;
	list<MovingCollidable*>::iterator i;
	for (i = movingCollidables.begin(); i != movingCollidables.end(); ++i){
		for (int j = 0; j < xyCounter; j++){
			res = res || xyWalls[j]->collide(*i, true);
		}
	}
	return res;
}

bool CollisionManager::checkYZCollisions(){
	bool res = false;
	list<MovingCollidable*>::iterator i;
	for (i = movingCollidables.begin(); i != movingCollidables.end(); ++i){
		for (int j = 0; j < yzCounter; j++){
			res = res || yzWalls[j]->collide(*i, true);
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

	fstream xyfile("collision/" + to_string(id) + "-xy.txt", ios_base::in);
	if (xyfile.is_open()){
		xyfile >> xyCounter;
		xyWalls = new Wall2D*[xyCounter];
		for (int i = 0; i < xyCounter; i++){
			xyfile >> a >> b >> c >> d;
			xyWalls[0] = new Wall2D(a, b, c, d);
		}
		xyfile.close();
	}

	fstream yzfile("collision/" + to_string(id) + "-yz.txt", ios_base::in);
	if (yzfile.is_open()){
		yzfile >> yzCounter;
		yzWalls = new Wall2D*[yzCounter];
		for (int i = 0; i < yzCounter; i++){
			yzfile >> a >> b >> c >> d;
			yzWalls[0] = new Wall2D(a, b, c, d);
		}
		yzfile.close();
	}
}