#include "stdafx.h"
#include "VoxelCollision.h"

/* # CONSTRUCTORS # */

/* VoxelCollision();
*  Description: 
*  Paramaters: 
*/

VoxelCollision::VoxelCollision(Player* Player, VoxelMap* world) 
{
	player = Player;
	D3DXVECTOR3 temp = player->getCamera()->GetPosition();
	Vector* position = new Vector;
	position->x = temp.x;
	position->y = temp.y;
	position->z = temp.z;
	collisionObject = CollisionObject(position, 1, 2, 1);
	map = world;
}

bool VoxelCollision::hasCollision()
{
	bool collision = false;
	D3DXVECTOR3 pos = player->getCamera()->GetPosition();
	Chunk* chunk = map->GetChunk(pos.x/CHUNK_SIZE, pos.z/CHUNK_SIZE);
	//if (chunk->chunk[pos.x%CHUNK_SIZE][pos.y%CHUNK_HEIGHT][pos.z%CHUNK_SIZE] != 0)
	Vector* point = new Vector;
	//point->x = pos.x;
	//point->y = pos.y;
	//point->z = pos.z;
	CollisionObject voxel = CollisionObject(point, 1, 1, 1);
	if (collisionObject.hasCollision(voxel, 0)) collision = true;
	return collision;
}

/* ~VoxelCollision();
*  Description: VoxelCollision class destructor.
*/
VoxelCollision::~VoxelCollision()
{
}