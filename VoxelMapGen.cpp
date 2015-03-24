#include "stdafx.h"
#include "VoxelMapGen.h"
#include "math.h"

int[16][16] heightMap;
string seed;

/* VoxelMapGen(string);
*  Description: Generates a voxel map from a given seed
*  Paramaters: seed : The starting seed for the map
*/
VoxelMapGen::VoxelMapGen(string givenSeed)
{
	int prev1;
	int prev2;
	int prev3;
	seed = givenSeed;
	//srand(seed); not implementing seeds yet
	for (int i = 0; i < 16; i++) { //row
		for (int j = 0; j < 16; j++) { //column
			if (j < 1 && i < 1) {
				prev1 = rand(108, 148);
				prev2 = rand(108, 148);
				prev3 = rand(108, 148);
				heightMap[i][j] = math.min(math.min(prev1, prev2), prev3);
			}
			else if (j < 1) {
				prev1 = rand(108, 148);
				prev2 = heightMap[i-1][j];
				prev3 = rand(108, 148);
				heightMap[i][j] = math.min(math.min(prev1, prev2), prev3);
			}
			else if (i < 1) {
				prev1 = rand(108, 148);
				prev2 = rand(108, 148);
				prev3 = heightMap[i][j-1];
				heightMap[i][j] = math.min(math.min(prev1, prev2), prev3);
			}
			else {
				prev1 = heightMap[i-1][j-1];
				prev2 = heightMap[i-1][j];
				prev3 = heightMap[i][j-1];
				heightMap[i][j] = math.min(math.min(prev1, prev2), prev3);
			}
		}
	}
}
/* VoxelMapGen();
*  Description: Generates a voxel map with a random seed
*/
VoxelMapGen::VoxelMapGen()
{
	seed = time(0);
	//srand(seed); not implementing seeds yet
}