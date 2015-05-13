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

	// Array of pointers to walls in XZ surface
	Wall2D ** xzWalls;

	// Number of walls in XZ surface
	int xzCounter;

	// Level ID
	int level;

	// Floor Y coordinate
	float floor;

	// Ceiling Y coordinate
	float ceiling;

	// List of moving collidables
	list<MovingCollidable*> movingCollidables;

	// Checking collisions between moving collidables, supporting inner function
	bool checkMovingCollisionsInner();

public:
	~CollisionManager();

	// Singleton accessor
	static CollisionManager* getInstance();

	// Adding moving collidable
	void addMovingCollidable(MovingCollidable* mc);

	// Removing moving collidable
	void removeMovingCollidable(MovingCollidable* mc);

	// Checking of collisions for all moving collidables
	bool checkCollisions();

	// Checking of wall collisions for all moving collidables
	bool checkXZCollisions();

	// Checking of floor/ceiling collisions for all moving collidables
	bool checkYCollisions();

	// Checking of collisions for single moving collidable
	bool checkCollisions(MovingCollidable* mc);

	// Checking of wall collisions for single moving collidable
	bool checkXZCollisions(MovingCollidable* mc);

	// Checking of floor/ceiling collisions for single moving collidable
	bool checkYCollisions(MovingCollidable* mc);

	// Checking of collisions between moving collidables
	bool checkMovingCollisions();

	// Loading of static collision setting for level
	void loadLevel(int id);
};