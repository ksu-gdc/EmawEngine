//Voxel collider
//Author: Ondrej Kuzela

#pragma once
#include "Collidable.h"

class VoxelObject : public Collidable
{
public:
	int getX();
	int getZ();
	int getHead();
	int getHeight();
	void fallDown();
	void jumpBack();

private:
	int x, z;
	int head;
	int height;
};