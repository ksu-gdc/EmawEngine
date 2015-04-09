//Voxel static collider
//Author: Ondrej Kuzela

#pragma once
#include "StaticCollider.h"
#include "VoxelMap.h"

class VoxelStatic : public StaticCollider
{
public:
	VoxelStatic(VoxelMap m);
	bool checkCollisions(list<Collidable> collidables);
	bool checkCollisions(Collidable c);
private:
	VoxelMap map;
};