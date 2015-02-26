#pragma once
#ifndef VOXELMAP_H
#define VOXELMAP_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <direct.h>

struct VoxRegion {
	int coord_X, coord_Y;
	int width = 16, length = 16, height = 256;
	short region[16][16][256] = {};
};

struct VoxMap {
	string seed;
	int width, height;
	int offset_X, offset_Y;
	int center_X, center_Y;
	vector< vector<VoxRegion> > grid;
};

class VoxelMap
{
public:
	VoxelMap(string);
	VoxelMap(string, string, int, int);
	bool SaveMap();
	VoxMap GetMap();
	bool LoadRegion(int, int);
	bool SaveRegion(int, int);
	bool RegionExists(int, int);
	~VoxelMap();

private:
	vector<string> Parse(string, char);
	void MakeDirectory(string);
	bool FileExists(string);
	pair<int, int> MapToRealCoord(int, int);
};
#endif