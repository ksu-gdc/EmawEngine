#include "stdafx.h"
#include "VoxelCollision.h"

/* # CONSTRUCTORS # */

/* VoxelCollision();
*  Description: 
*  Paramaters: 
*/

VoxelCollision::VoxelCollision(Player* Player, Grid* world) 
{
	player = Player;
	D3DXVECTOR3 temp = player->getCamera()->GetPosition();
	//Vector* position = new Vector;
	position->x = temp.x;
	position->y = temp.y;
	position->z = temp.z;
	collisionObject = CollisionObject(position, 1, 2, 1);
	map = world;
}

void VoxelCollision::Update()
{
	D3DXVECTOR3 temp = player->getCamera()->GetPosition();
	position->x = temp.x;
	position->y = temp.y;
	position->z = temp.z;
	//TODO: change chunks depending on where you are in the map
}

bool VoxelCollision::hasCollision()
{
	bool collision = false;
	for each (vector<Chunk> row in map->grid)
	{
		for each (Chunk chunk in row)
		{
			//TODO: figure out how to check with voxels
			for each (short top in chunk.height_map) {
				if (position->y < top) return true;
			}
		}
	}

	return collision;
}

/* ~VoxelCollision();
*  Description: VoxelCollision class destructor.
*/
VoxelCollision::~VoxelCollision()
{
}