//Collision manager
//Author: Ondrej Kuzela

#pragma once
#include "Wall2D.h"
#include "MovingCollidable.h"
#include <list>

using namespace std;

class CollisionManager {
private:
	CollisionManager();

	// Statics
	static bool instanceFlag;
	static CollisionManager *instance;

	Wall2D ** xyWalls;
	int xyCounter;

	Wall2D ** yzWalls;
	int yzCounter;

	list<MovingCollidable*> movingCollidables;

	bool checkMovingCollisionsInner();

public:
	~CollisionManager();

	// Singleton accessor
	static CollisionManager* getInstance();

	void addMovingCollidable(MovingCollidable* mc);

	void removeMovingCollidable(MovingCollidable* mc);

	bool checkCollisions();

	bool checkXYCollisions();

	bool checkYZCollisions();

	bool checkMovingCollisions();

	void loadLevel(int id);
};