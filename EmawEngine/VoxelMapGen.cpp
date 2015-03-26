#include "stdafx.h"
#include "VoxelMapGen.h"
#include "math.h"

int[16][16] heightMap;
string seed;

/* VoxelMapGen(string);
*  Description: Generates a voxel map from a given seed
*  Paramaters: seed : The starting seed for the map
*/
Chunk VoxelMapGen::VoxelMapGen(float f[16][16], int x, int y, int freq, int floor, int ceiling)
{
	Chunk vr;
	short id = 1;

	vr.coord_X = x;
	vr.coord_Y = y;
	memset(vr.chunk, 0, sizeof(vr.chunk));

	int prev1;
	int prev2;
	int prev3;
	int curr;
	seed = givenSeed;
	//srand(seed); not implementing seeds yet
	if (freq > 0 && floor > 0 && ceiling > floor)
	{
		if ((freq + floor) < vr.height)
		{
			for (int i = 0; i < vr.length; i++)
			{
				for (int j = 0; j < vr.width; j++)
				{
					if (j < 1 && i < 1) {
						prev1 = rand(floor, floor + freq);
						prev2 = rand(floor, floor + freq);
						prev3 = rand(floor, floor + freq);
						curr = rand(floor, floor + freq);
						heightMap[i][j] = (prev1 + prev2 + prev3 + curr) / 4;
					}
					else if (j < 1) {
						prev1 = rand(floor, floor + freq);
						prev2 = heightMap[i - 1][j];
						prev3 = rand(floor, floor + freq);
						curr = rand(floor, floor + freq);
						heightMap[i][j] = (prev1 + prev2 + prev3 + curr) / 4;
					}
					else if (i < 1) {
						prev1 = rand(floor, floor + freq);
						prev2 = rand(floor, floor + freq);
						prev3 = heightMap[i][j - 1];
						curr = rand(floor, floor + freq);
						heightMap[i][j] = (prev1 + prev2 + prev3 + curr) / 4;
					}
					else {
						prev1 = heightMap[i - 1][j - 1];
						prev2 = heightMap[i - 1][j];
						prev3 = heightMap[i][j - 1];
						curr = rand(floor, floor + freq);
						heightMap[i][j] = (prev1 + prev2 + prev3 + curr) / 4;
					}
				}
			}
		}
	}
	return vr;
}
/* VoxelMapGen();
*  Description: Generates a voxel map with a random seed
*/
VoxelMapGen::VoxelMapGen()
{
	seed = time(0);
	//srand(seed); not implementing seeds yet
}