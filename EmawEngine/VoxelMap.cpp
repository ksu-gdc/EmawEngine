#include "stdafx.h"
#include "VoxelMap.h"

VoxMap map;
string directory;

/* VoxelMap(string);
*  Description: Attempts to load a VoxelMap from the specified directory.
*  Paramaters: dir : The directory which holds a valid map file to construct a VoxelMap object in memory with.
*/
VoxelMap::VoxelMap(string dir)
{
	ifstream file(dir + "map.dat");

	if (file.good())
	{
		string line;
		VoxRegion blank;

		memset(blank.region, 0, sizeof(blank.region));

		while (getline(file, line))
		{
			vector<string> tokens = Parse(line, '=');

			if (tokens[0] == "Seed")
			{
				map.seed = tokens[1];
			}
			else if (tokens[0] == "Directory")
			{
				directory = tokens[1];
			}
			else if (tokens[0] == "Center_X")
			{
				map.center_X = atoi(tokens[1].c_str());
			}
			else if (tokens[0] == "Center_Y")
			{
				map.center_Y = atoi(tokens[1].c_str());
			}
			else if (tokens[0] == "Width")
			{
				map.width = atoi(tokens[1].c_str());
			}
			else if (tokens[0] == "Height")
			{
				map.height = atoi(tokens[1].c_str());
			}
		}

		file.close();

		map.offset_X = (int)floor(map.width / 2);
		map.offset_Y = (int)floor(map.height / 2);
		map.grid = vector<vector<VoxRegion>>(map.width, vector<VoxRegion>(map.height, blank));
	}
	else
	{
		file.close();
		throw invalid_argument("No such file exists.");
	}
}

/* VoxelMap(string, string, width, height);
*  Description: Creates a NEW VoxelMap class object with the defining parameters.
*  Parameters: dir : The directory to save the VoxelMap object, data, and resources.
*			   seed : The world generator seed, used to generate contiguous terrain.
*			   width : Specifies how many horizontal chunks will be loaded at once.
*			   height : Specifies how many vertical chunks will be loaded at once.
*/
VoxelMap::VoxelMap(string dir, string seed, int width, int height)
{
	VoxRegion blank;

	memset(blank.region, 0, sizeof(blank.region));

	if ((width % 2) != 1 && width > 0) width += 1;
	if ((height % 2) != 1 && height > 0) height += 1;

	map = {
		seed,
		width,
		height,
		(int)floor(map.width / 2),
		(int)floor(map.height / 2),
		0,
		0,
		vector<vector<VoxRegion>>(map.width, vector<VoxRegion>(map.height, blank))
	};

	MakeDirectory(dir);
	MakeDirectory(dir + "Regions/");
	directory = dir;

	SaveMap();
}

/* SaveMap();
*  Description: Updates the directory's map file. Returns a bool indicating success of failure.
*  Returns: bool : Indiciates success or failure of save operation.
*/
bool VoxelMap::SaveMap()
{
	ofstream file(directory + "map.dat", ofstream::out | ofstream::trunc);

	if (file.good())
	{
		file << "Seed=" << map.seed << endl;
		file << "Directory=" << directory << endl;
		file << "Width=" << map.width << endl;
		file << "Height=" << map.height << endl;
		file << "Center_X=" << map.center_X << endl;
		file << "Center_Y=" << map.center_Y << endl;
		file.close();

		//TO DO: Add code to save regions existing on the map's grid. 

		return true;
	}
	else return false;
}

/* GetMap();
*  Description: Retrieves the VoxMap object, and returns it.
*  Returns: VoxMap
*/
VoxMap VoxelMap::GetMap() { return map; }

/* LoadRegion(int, int);
*  Description: Attempts to load a region file at the specified coordinates.
*  Returns: bool : Indicates success or failure of load operation.
*  Parameters: coord_x : X coordinate of the Region to be loaded.
*			   coord_y : Y coordinate of the Region to be loaded.
*/
bool VoxelMap::LoadRegion(int coord_x, int coord_y)
{
	pair<int, int> coords = MapToRealCoord(coord_x, coord_y);

	if (coords.first < map.width && coords.second < map.height)
	{
		string name = "r." + to_string(coord_x) + "." + to_string(coord_y) + ".dat";
		ifstream file(directory + "Regions/" + name);
		VoxRegion vr = map.grid[coords.first][coords.second];

		memset(vr.region, 0, sizeof(vr.region));

		//If the region files exists in the directory. 
		if (file.good())
		{
			string line;
			int palette, row;

			while (getline(file, line))
			{
				vector<string> tmp = Parse(line, '=');

				if (tmp[0] == "PALETTE")
				{
					palette = atoi(tmp[1].c_str());
				}
				else
				{
					row = atoi(tmp[0].c_str());
					vector<string> cols = Parse(tmp[1], ',');

					for (size_t a = 0; a < cols.size(); a++)
					{
						vr.region[row][a][palette] = (short)atoi(cols[a].c_str());
					}
				}
			}
		}

		map.grid[coords.first][coords.second] = vr;
		file.close();

		return true;
	}
	return false;
}

/* SaveRegion(int, int);
*  Description: Attempts to save a region to file.
*  Returns: bool : Indicates success or failure of save operation.
*  Parameters: coord_x : X coordinate of the Region to be loaded.
*			   coord_y : Y coordinate of the Region to be loaded.
*/
bool VoxelMap::SaveRegion(int coord_x, int coord_y)
{
	pair<int, int> coords = MapToRealCoord(coord_x, coord_y);

	if (coords.first < map.width && coords.second < map.height)
	{
		VoxRegion vr = map.grid[coords.first][coords.second];
		string name = "r." + to_string(coord_x) + "." + to_string(coord_y) + ".dat";
		ofstream file(directory + "Regions/" + name, ofstream::out | ofstream::trunc);

		if (file.good()) {
			for (int a = 0; a < vr.height; a++)
			{
				file << "PALETTE=" << a << endl;
				for (int b = 0; b < vr.length; b++)
				{
					file << b << "=";
					for (int c = 0; c < vr.width; c++)
					{
						if (c == (vr.width - 1))
						{
							file << vr.region[b][c][a] << endl;
						}
						else
						{
							file << vr.region[b][c][a] << ",";
						}
					}
				}
			}
			file.close();
			return true;
		}
	}

	return false;
}

/* RegionExists(int, int);
*  Description: Checks if the region with the specified coordinates exists on the map.
*  Returns: bool : Indicates true if the region is loaded, false  otherwise.
*  Parameters:
*/
bool VoxelMap::RegionExists(int coord_x, int coord_y)
{
	pair<int, int> coords = MapToRealCoord(coord_x, coord_y);

	if (coords.first < map.width && coords.second < map.height)
	{
		VoxRegion vr = map.grid[coords.first][coords.second];

		if (vr.coord_X == coord_x && vr.coord_Y == coord_y)
		{
			return true;
		}
	}

	return false;
}

/* (int, int, int);
*  Description:
*  Returns:
*  Parameters:
*/
float** VoxelMap::CreateChunk(int freq, int floor, int ceiling)
{
	float** heightMap;
	heightMap = new float*[16];

	for (int i = 0; i < 16; i++) 
	{
		heightMap[i] = new float[16];
	}

	//Generate key values
	for (int i = 0; i < 16; i += freq)
	{
		for (int j = 0; j < 16; j += freq)
		{
			heightMap[i][j] = rand() % ceiling + floor;
		}
		heightMap[i][15] = rand() % ceiling + floor;
	}
	for (int i = 0; i < 16; i += freq)
	{
		heightMap[15][i] = rand() % ceiling + floor;
	}
	heightMap[15][15] = rand() % ceiling + floor;

	//Generate row bridge values
	float key1 = heightMap[0][0];
	float key2 = heightMap[freq][freq];
	float step = key2 - key1;
	for (int j = 0; j < 16; j += freq)
	{
		for (int i = 1; i < 15; i++)
		{
			if (16%i != 0)
			{
				heightMap[i][j] = heightMap[i - 1][j] + step;
			}
			else 
			{
				key1 = key2;
				if (i + freq > 16)
				{
					key2 = heightMap[i+freq][j];
				}
				else key2 = heightMap[15][j];
				step = key2 - key1;
			}
		}
	}
	//final row
	for (int i = 1; i < 15; i++)
	{
		if (16 % i != 0)
		{
			heightMap[i][15] = heightMap[i - 1][15] + step;
		}
		else
		{
			key1 = key2;
			if (i + freq > 16)
			{
				key2 = heightMap[i + freq][15];
			}
			else key2 = heightMap[15][15];
			step = key2 - key1;
		}
	}

	//Genrate column values
	for (int i = 0; i < 16; i += freq)
	{
		for (int j = 1; j < 15; j++)
		{
			if (16 % i != 0)
			{
				heightMap[i][j] = heightMap[i][j - 1] + step;
			}
			else
			{
				key1 = key2;
				if (j + freq > 16)
				{
					key2 = heightMap[i][j + freq];
				}
				else key2 = heightMap[i][15];
				step = key2 - key1;
			}
		}
	}
	//final row
	for (int j = 1; j < 15; j++)
	{
		if (16 % j != 0)
		{
			heightMap[15][j] = heightMap[15][j - 1] + step;
		}
		else
		{
			key1 = key2;
			if (j + freq > 16)
			{
				key2 = heightMap[15][j + freq];
			}
			else key2 = heightMap[15][15];
			step = key2 - key1;
		}
	}

	//Generate filler values
	for (int i = 1; i < 15; i++)
	{
		if (16 % i != 0)
		{
			for (int j = 1; j < 15; j++)
			{
				if (16 % j != 0)
				{
					heightMap[i][j] = (heightMap[i][j - 1] + heightMap[i - 1][j]) / 2;
				}
			}
		}
	}

	//Prepare for returning
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			heightMap[i][j] = heightMap[i][j] / ceiling;
		}
	}

	return heightMap;
}

/* ~VoxelMap();
*  Description: VoxelMap class destructor.
*/
VoxelMap::~VoxelMap()
{
}

/* Parse(string, char);
*  Description: Tokenizes a string by the supplied delimiter, and returns a vector of tokens.
*  Returns: vector<string>
*  Parameters: line : The string object to tokenize.
*			   delim : The character delimiter on which to parse substrings.
*/
vector<string> VoxelMap::Parse(string line, char delim)
{
	vector<string> tokens;
	size_t index;

	while ((index = line.find(delim)) != string::npos)
	{
		tokens.push_back(line.substr(0, index));
		line = line.substr(index + 1);
	}

	tokens.push_back(line);
	return tokens;
}

/* MakeDirectory(string, char);
*  Description: Creates a directory, and sub directories, of an otherwise abstract directory path.
*  Returns: void
*  Parameters: dir : The directory path to build.
*			   delim : The character which to parse the path string with.
*/
void VoxelMap::MakeDirectory(string dir)
{
	char delim;
	string path;

	if (count(dir.begin(), dir.end(), '/') > count(dir.begin(), dir.end(), '\\')) delim = '/';
	else delim = '\\';

	vector<string> tmp = Parse(dir, delim);

	for (string s : tmp)
	{
		path += s + delim;

		if (!FileExists(path))
		{
			mkdir(path.c_str());
		}
	}
}

/* FileExists(string);
*  Description: Checks if a File and/or directory exists, and returns a boolean value.
*  Returns: bool : Returns true or false depending on whether or not the file/directory exists.
*  Parameters: path : The file path checked for validity.
*/
bool VoxelMap::FileExists(string path)
{
	DWORD attr = GetFileAttributes((LPWSTR)path.c_str());

	switch (attr)
	{
	case INVALID_FILE_ATTRIBUTES:
		return false;
	default:
		return true;
	}
}

/* MapToRealCoord(int, int);
*  Description: Checks if a File and/or directory exists, and returns a boolean value.
*  Returns: bool : Returns true or false depending on whether or not the file/directory exists.
*  Parameters: coord_x : The virtual coordinate to translate to the according 2D array row index.
*			   coord_y : The virtual coordinate to translate to the according 2D array column index.
*/
pair<int, int> VoxelMap::MapToRealCoord(int coord_x, int coord_y)
{
	pair<int, int> coords;

	if (coord_x < map.center_X)
	{
		coords.first = (map.offset_X - map.center_X) - abs(coord_x);
	}
	else
	{
		coords.first = (map.offset_X - map.center_X) + abs(coord_x);
	}

	if (coord_y < map.center_Y)
	{
		coords.second = (map.offset_Y - map.center_Y) - coord_y;
	}
	else
	{
		coords.second = (map.offset_Y - map.center_Y) + coord_y;
	}

	return coords;
}