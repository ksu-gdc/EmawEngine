#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <direct.h>

using namespace std;

struct Chunk {
	int coord_X, coord_Y;
	bool set;
	static const int width = 17, length = 17, height = 225;
	short height_map[17][17];
	short chunk[17][17][225];
};

struct Grid {
	string seed, directory;
	int width, height;
	int offset_X, offset_Y;
	int center_X, center_Y;
	vector< vector<Chunk> > grid;
};

enum Adjacent : int {
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

class VoxelMap
{
public:
	VoxelMap(string);
	VoxelMap(string, string, int, int);
	Grid GetMap();
	bool SaveMap();
	void SetMapCenter(int, int);
	void SetMapSize(int);
	bool LoadChunk(int, int);
	void SaveChunk(Chunk);
	Chunk CreateChunk(int, int, string, int, int);
	void CreateChunk(Chunk);
	~VoxelMap();
	vector< vector<short> > GenerateHeightMap(int, int, int, int, int, int, vector<vector<short>>);
	int GeneratePsuedoKey(int, int);
	bool IsChunkAdjacent(int, int, Adjacent);

private:
	vector<string> Parse(string, char);
	void MakeDirectory(string);
	bool FileExists(string);
	fstream GetFileHandle(string, ios::openmode);
	pair<int, int> MapToRealCoord(int, int);
	pair<int, int> MapToVirtualCoord(int, int);
};