#pragma once

struct VoxRegion {
	int coord_X, coord_Y;
	static const int width = 16, length = 16, height = 256;
	short region[16][16][256];
};

struct VoxMap {
	string seed;
	int width, height;
	int offset_X, offset_Y;
	int center_X, center_Y;
	vector< vector<VoxRegion> > grid;
};

class VoxelMap : public Asset
{
public:
	VoxelMap(string);
	VoxelMap(string, string, int, int);
	bool SaveMap();
	VoxMap GetMap();
	bool LoadRegion(int, int);
	bool SaveRegion(int, int);
	bool RegionExists(int, int);
	float** CreateChunk(int, int, int);
	~VoxelMap();

private:
	vector<string> Parse(string, char);
	void MakeDirectory(string);
	bool FileExists(string);
	pair<int, int> MapToRealCoord(int, int);
};