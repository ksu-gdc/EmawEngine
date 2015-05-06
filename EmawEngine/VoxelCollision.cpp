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
	D3DXVECTOR3 pos = player->getCamera()->GetPosition();
	Chunk* chunk = map->GetChunk(pos.x/CHUNK_SIZE, pos.z/CHUNK_SIZE);
	//if (chunk->chunk[pos.x%CHUNK_SIZE][pos.y%CHUNK_HEIGHT][pos.z%CHUNK_SIZE] != 0)
	Vector* point = new Vector;
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			point->x = i + pos.x;
			point->y = chunk->height_map[i][j];
			point->z = j + pos.z;
			if (collisionObject.hasCollision(CollisionObject(point, 1, 1, 1), 0)) return true;
		}
	}
	return false;
}

/* ~VoxelCollision();
*  Description: VoxelCollision class destructor.
*/
VoxelCollision::~VoxelCollision()
{
}