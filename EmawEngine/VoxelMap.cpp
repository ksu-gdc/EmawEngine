#include "stdafx.h"
#include "VoxelMap.h"



/* # CONSTRUCTORS # */

/* VoxelMap(string);
*  Description: Attempts to load a VoxelMap class from the specified directory.
*  Paramaters: dir : The directory which holds a valid map file to construct a VoxelMap object in memory with.
*/
VoxelMap::VoxelMap(string dir)
{
	Chunk blank;
	fstream file(map.directory + "/map.dat", ios::in);

	memset(blank.chunk, 0, sizeof(blank.chunk));

	if (file.good())
	{
		string line;

		while (getline(file, line))
		{
			vector<string> tokens = Parse(line, '=');

			if (tokens[0] == "Seed")
			{
				map.seed = stoi(tokens[1]);
			}
			else if (tokens[0] == "Size")
			{
				map.size = abs(atoi(tokens[1].c_str()));
			}
			else if (tokens[0] == "Center_X")
			{
				map.center_X = atoi(tokens[1].c_str());
			}
			else if (tokens[0] == "Center_Y")
			{
				map.center_Y = atoi(tokens[1].c_str());
			}
		}

		file.close();

		map.offset = floor(map.size / 2);
		map.grid = vector<vector<Chunk>>(map.size, vector<Chunk>(map.size, blank));

		PopulateMap();
	}
	else
	{
		VoxelMap(dir, dir, 16);
	}
}

/* VoxelMap(string, string, int, int);
*  Description: Creates a new VoxelMap class.
*  Parameters: dir : The directory in which to save this VoxelMap class.
*			  seed : The world generation seed.
*                x : The width of the map.
*                y : The height of the map.
*/
VoxelMap::VoxelMap(string dir, string seed, int size)
{
	Chunk blank;
	hash<string> hash;

	memset(blank.chunk, 0, sizeof(blank.chunk));

	map = {
		dir,
		hash(seed),
		size,
		floor(size / 2),
		0,
		0,
		vector<vector<Chunk>>(size, vector<Chunk>(size, blank))
	};

	MakeDirectory(dir + "/");
	SaveMap();
	PopulateMap();
}

/* # PUBLIC FUNCTIONS # */

/* SaveMap();
*  Description: Updates the directory's map file. Returns a bool indicating success of failure.
*  Returns: bool
*/
bool VoxelMap::SaveMap()
{
	fstream file(map.directory + "/map.dat", ios::out | ios::trunc);

	if (file.good())
	{
		file << "Seed=" << map.seed << endl;
		file << "Directory=" << map.directory << endl;
		file << "Size=" << map.size << endl;
		file << "Center_X=" << map.center_X << endl;
		file << "Center_Y=" << map.center_Y << endl;

		file.close();

		return true;
	}
	return false;
}

/*
*  Description:
*  Returns:
*  Parameters:
*/
void VoxelMap::PopulateMap()
{
	for (int a = 0; a < map.size; a++)
	{
		for (int b = 0; b < map.size; b++)
		{
			map.grid[a][b] = CreateChunk(a, b, 2, 5);
		}
	}
}

/* LoadChunk(int, int);
*  Description: Attempts to load a chunk file at the specified coordinates.
*  Returns: bool
*  Parameters: coord_x : X coordinate of the Region to be loaded.
*			   coord_y : Y coordinate of the Region to be loaded.
*/
bool VoxelMap::LoadChunk(int coord_x, int coord_y)
{
	pair<int, int> coords = MapToVirtualCoord(coord_x, coord_y);

	if (coord_x < map.size && coord_y < map.size)
	{
		Chunk vr = map.grid[coord_x][coord_y];
		string line, name = "r." + to_string(coords.first) + "." + to_string(coords.second) + ".hmap";
		fstream file(map.directory + "Regions/" + name, ios::in);
		memset(vr.chunk, 0, sizeof(vr.chunk));

		if (file.good())
		{
			while (getline(file, line))
			{
				vector<string> tmp = Parse(line, '=');
				vector<string> cols = Parse(tmp[1], ',');

				int row = atoi(tmp[0].c_str());

				for (size_t a = 0; a < cols.size(); a++)
				{
					vr.height_map[row][a] = (short)atoi(cols[a].c_str());
				}
			}

			CreateChunk(vr);
			file.close();
		}
		else
		{
			//TO DO : Create variables for floor, and frequency. 
			vr = CreateChunk(coords.first, coords.second, 10, 5);
		}

		map.grid[coords.first][coords.second] = vr;

		return true;
	}
	return false;
}

/* SaveChunk(Chunk);
*  Description: Attempts to save a chunk to file.
*  Returns: bool
*  Parameters: ch : The Chunk struct being written to file. 
*/
void VoxelMap::SaveChunk(Chunk ch)
{
	string name = "r." + to_string(ch.coord_X) + "." + to_string(ch.coord_Y) + ".hmap";
	fstream file = GetFileHandle(map.directory + "Regions/" + name, ios::out | ios::trunc);

	if (file.good())
	{
		for (int a = 0; a < CHUNK_SIZE; a++)
		{
			file << a << "=";

			for (int b = 0; b < CHUNK_SIZE; b++)
			{
				file << ch.height_map[a][b];

				if (b == (CHUNK_SIZE - 1))
				{
					file << endl;
				}
				else
				{
					file << ",";
				}
			}
		}
		file.close();
	}
}

/* CreateChunk(int, int, int, int);
*  Description: Creates a Chunk struct located at the specified coordinates in world space. 
*  Returns: Chunk
*  Parameters: coord_x : The X coordinate of the new Chunk struct in world space. 
*			   coord_y : The Y coordinate of the new Chunk struct in world space. 
*			      freq : Determines the Chunk struct's terrain topography.
*                floor : The minimum amount of blocks at any given pair of coordinates. 
*/
Chunk VoxelMap::CreateChunk(int coord_x, int coord_y, int freq, int floor)
{
	if ((freq > 0 && freq < 51) && floor < 101)
	{
		pair<int, int> coords = MapToVirtualCoord(coord_x, coord_y);
		short height[CHUNK_SIZE][CHUNK_SIZE];
		int offset = INT_MAX / 2;
		Chunk ch = {
			coord_x,
			coord_y
		};

		//Generates initial 2D noise table.
		GenerateNoise();

		//Translates and smooths the original noise generation, and inserts value into table.
		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				height[x][y] = floor + (Turbulence(offset + (coords.first * CHUNK_SIZE) + x, offset + (coords.second * CHUNK_SIZE) + y, 64) / freq);
			}
		}

		memset(ch.chunk, 0, sizeof(ch.chunk));

		for (int a = 0; a < CHUNK_SIZE; a++)
		{
			for (int b = 0; b < CHUNK_SIZE; b++)
			{
				ch.height_map[a][b] = height[a][b];

				for (int c = 0; c < height[a][b]; c++)
				{
					ch.chunk[a][b][c] = (short)1;
				}
			}
		}

		return ch;
	}
	throw invalid_argument("Invalid frequency value. Frequency must be between 1, and 50.");
}

/* CreateChunk(Chunk ch);
*  Description: Takes in a Chunk struct and fills in it's 3D structure
*  Returns: void
*  Parameters: ch : The Chunk struct to fill in the 3D world space for.
*/
void VoxelMap::CreateChunk(Chunk ch)
{
	for (int a = 0; a < CHUNK_SIZE; a++)
	{
		for (int b = 0; b < CHUNK_SIZE; b++)
		{
			for (int c = 0; c < ch.height_map[a][b]; c++)
			{
				ch.chunk[a][b][c] = (short)1;
			}
		}
	}
}

/* GetChunk(int, int);
*  Description: Retrieves a Chunk struct in memory, and returns a pointer to it. 
*  Returns: Chunk*
*  Parameters:
*/
Chunk* VoxelMap::GetChunk(int grid_x, int grid_y)
{
	if ((grid_x > -1 && grid_x < map.size) && (grid_y > -1 && grid_y < map.size))
	{
		return &map.grid[grid_x][grid_y];
	}
}

/* GetChunkValue(int, int, int, int, int);
*  Description: Returns a value stored inside the designated Chunk struct.
*  Returns: short
*  Parameters: grid_x : The X coordinate of the Chunk struct in storage space.
*			   grid_y : The Y coordinate of the Chunk struct in storage space.
*			  chunk_x : The X coordinate of the Chunk's 3D short value in storage space.
*			  chunk_y : The Y coordinate of the Chunk's 3D short value in storage space.
*			  chunk_z : The Z coordinate of the Chunk's 3D short value in storage space.
*/
short VoxelMap::GetChunkValue(int grid_x, int grid_y, int chunk_x, int chunk_y, int chunk_z)
{
	if ((grid_x > -1 && grid_x < map.size) && (grid_y > -1 && grid_y < map.size))
	{
		Chunk ch = map.grid[grid_x][grid_y];

		if ((chunk_x > -1 && chunk_x < CHUNK_SIZE) && (chunk_y > -1 && chunk_y < CHUNK_SIZE))
		{
			if (chunk_z > -1 && chunk_z < CHUNK_HEIGHT)
			{
				return ch.chunk[chunk_x][chunk_y][chunk_z];
			}
		}
	}
	return -1;
}

/* ~VoxelMap();
*  Description: VoxelMap class destructor.
*/
VoxelMap::~VoxelMap()
{
}

/* # PRIVATE FUNCTIONS # */

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
			_mkdir(path.c_str());
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

/* GetFileHandle();
*  Description: Opens a file and returns the handle, otherwise throws an exception if no file is found. 
*  Returns: fstream
*  Parameters: dir : The location of the file to open. 
*            modes : The modes and flags with which to open the designated file with. 
*/
fstream VoxelMap::GetFileHandle(string dir, ios::openmode modes)
{
	fstream file(dir, modes);

	if (file.good())
	{
		return file;
	}
	else
	{
		file.close();
		throw invalid_argument("No such file exists.");
	}
}

/* MapToRealCoord(int, int);
*  Description: Translates a set of virtual coordinates, to actual vector coordinates.
*  Returns: pair<int, int> : Holds the set of translated coordinates.
*  Parameters: coord_x : The virtual coordinate to translate to the according 2D array row index.
*			   coord_y : The virtual coordinate to translate to the according 2D array column index.
*/
pair<int, int> VoxelMap::MapToRealCoord(int coord_x, int coord_y)
{
	pair<int, int> coords(coord_x + map.offset, coord_y + map.offset);
	return coords;
}


/* MapToVirtualCoord(int, int);
*  Description : Translates a set of real vector coordinates, to a set of virtual coordinates.
*  Returns : pair<int, int> : Holds the set of translated coordinates.
*  Parameters : coord_x : The real coordinate to translate to it's according index in virtual space.
*               coord_y : The real coordinate to translate to it's according index in virtual space.
*/
pair<int, int> VoxelMap::MapToVirtualCoord(int coord_x, int coord_y)
{
	pair<int, int> coords(coord_x - map.offset, coord_y - map.offset);
	return coords;
}

/* GenerateNoise();
*  Description: Generates a basic Noise table used to generate terrain.
*  Returns: void 
*  Parameters:
*/
void VoxelMap::GenerateNoise()
{
	memset(Noise, 0, sizeof(Noise));

	srand(map.seed);

	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			Noise[x][y] = (rand() % 32768) / 32768.0;
		}
	}
}

/* SmoothNoise(double, double);
*  Description: Smooths a value picked from the Noise table.
*  Returns: double 
*  Parameters: x : X coordinate on the Noise table.
*			   y : Y coordinate on the Noise table.
*/
double VoxelMap::SmoothNoise(double x, double y)
{
	double fractX = x - int(x);
	double fractY = y - int(y);

	int x1 = (int(x) + CHUNK_SIZE) % CHUNK_SIZE;
	int y1 = (int(y) + CHUNK_SIZE) % CHUNK_SIZE;

	int x2 = (x1 + CHUNK_SIZE - 1) % CHUNK_SIZE;
	int y2 = (y1 + CHUNK_SIZE - 1) % CHUNK_SIZE;

	double value = 0.0;
	value += fractX       * fractY       * Noise[x1][y1];
	value += fractX       * (1 - fractY) * Noise[x1][y2];
	value += (1 - fractX) * fractY       * Noise[x2][y1];
	value += (1 - fractX) * (1 - fractY) * Noise[x2][y2];

	return value;
}

/* Turbulence(double, double, double);
*  Description: Further obfuscates and smooths the Noise table, resulting in gradient style terrain.
*  Returns: double
*  Parameters: x : X coordinate on the Noise table.
*			   y : Y coordinate on the noise table.
*			size : Sampling size. 
*/
double VoxelMap::Turbulence(double x, double y, double size)
{
	double value = 0.0, initialSize = size;

	while (size >= 1)
	{
		value += SmoothNoise(x / size, y / size) * size;
		size /= 2.0;
	}

	return(128.0 * value / initialSize);
}