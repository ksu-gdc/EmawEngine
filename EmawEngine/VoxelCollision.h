#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <direct.h>
#include "CollisionObject.h"
#include "Player.h"

using namespace std;

class VoxelCollision
{
public:
	//Global objects
	Player* player;
	Vector* position;
	CollisionObject collisionObject;
	Grid* map;
	Chunk* chunk;

	//Class Functions, and Constructor/Destructor.
	VoxelCollision(Player*, Grid*);
	bool hasCollision();
	void Update();
	~VoxelCollision();
private:
};