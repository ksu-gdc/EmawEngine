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

	Wall2D ** xzWalls;
	int xzCounter;

	int level;
	float floor;
	float ceiling;

	list<MovingCollidable*> movingCollidables;

	bool checkMovingCollisionsInner();

public:
	~CollisionManager();

	// Singleton accessor
	static CollisionManager* getInstance();

	void addMovingCollidable(MovingCollidable* mc);

	void removeMovingCollidable(MovingCollidable* mc);

	bool checkCollisions();

	bool checkXZCollisions();

	bool checkYCollisions();

	bool checkCollisions(MovingCollidable* mc);

	bool checkXZCollisions(MovingCollidable* mc);

	bool checkYCollisions(MovingCollidable* mc);

	bool checkMovingCollisions();

	void loadLevel(int id);
};