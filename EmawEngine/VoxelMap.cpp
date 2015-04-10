#include "stdafx.h"
#include "VoxelMap.h"

Grid map;

/* # CONSTRUCTORS # */

/* VoxelMap(string);
*  Description: Attempts to load a VoxelMap class object from the specified directory.
*  Paramaters: dir : The directory which holds a valid map file to construct a VoxelMap object in memory with.
*/
VoxelMap::VoxelMap(string dir)
{
	Chunk blank;
	fstream file(map.directory + "map.dat", ios::in);

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
			else if (tokens[0] == "Width")
			{
				map.width = abs(atoi(tokens[1].c_str()));
			}
			else if (tokens[0] == "Height")
			{
				map.height = abs(atoi(tokens[1].c_str()));
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

		map.offset_X = floor(map.width / 2);
		map.offset_Y = floor(map.height / 2);
		map.grid = vector<vector<Chunk>>(map.width, vector<Chunk>(map.height, blank));

		PopulateMap();
	}
	else
	{
		VoxelMap(dir, dir, 20, 20);
	}
}

/*
*  Description:
*  Returns:
*  Parameters:
*/
VoxelMap::VoxelMap(string dir, string seed, int x, int y)
{
	Chunk blank;
	hash<string> hash;

	memset(blank.chunk, 0, sizeof(blank.chunk));

	map = {
		dir,
		hash(seed),
		x,
		y,
		floor(x / 2),
		floor(y / 2),
		0,
		0,
		vector<vector<Chunk>>(x, vector<Chunk>(y, blank))
	};

	SaveMap();
	PopulateMap();
}

/*
*	Desctiption:
*	Returns:
*	Parameters:
*/
VoxelMap::~VoxelMap()
{


}

/* # PUBLIC FUNCTIONS # */

/* SaveMap();
*  Description: Updates the directory's map file. Returns a bool indicating success of failure.
*  Returns: bool : Indiciates success or failure of save operation.
*/
bool VoxelMap::SaveMap()
{
	fstream file(map.directory + "map.dat", ios::out | ios::trunc);

	if (file.good())
	{
		file << "Seed=" << map.seed << endl;
		file << "Directory=" << map.directory << endl;
		file << "Width=" << map.width << endl;
		file << "Height=" << map.height << endl;
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
	for (int a = 0; a < map.width; a++)
	{
		for (int b = 0; b < map.height; b++)
		{
			map.grid[a][b] = CreateChunk(a, b, 50, 5);
		}
	}
}

/* GetChunk(int, int);
*  Description: Attempts to load a chunk file at the specified coordinates.
*  Returns: bool : Indicates success or failure of load operation.
*  Parameters: coord_x : X coordinate of the Region to be loaded.
*			   coord_y : Y coordinate of the Region to be loaded.
*/
bool VoxelMap::LoadChunk(int coord_x, int coord_y)
{
	pair<int, int> coords = MapToVirtualCoord(coord_x, coord_y);

	if (coord_x < map.width && coord_y < map.height)
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

/* SaveChunk(int, int);
*  Description: Attempts to save a chunk to file.
*  Returns: bool : Indicates success or failure of save operation.
*  Parameters: coord_x : X coordinate of the Region to be loaded.
*			   coord_y : Y coordinate of the Region to be loaded.
*/
void VoxelMap::SaveChunk(Chunk ch)
{
	string name = "r." + to_string(ch.coord_X) + "." + to_string(ch.coord_Y) + ".hmap";
	fstream file = GetFileHandle(map.directory + "Regions/" + name, ios::out | ios::trunc);

	if (file.good())
	{
		for (int a = 0; a < ch.size; a++)
		{
			file << a << "=";

			for (int b = 0; b < ch.size; b++)
			{
				file << ch.height_map[a][b];

				if (b == (ch.size - 1))
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

/* CreateChunk(int, int, string, int, int);
*  Description:
*  Returns:
*  Parameters:
*/
Chunk VoxelMap::CreateChunk(int coord_x, int coord_y, int freq, int floor)
{
	Chunk ch = {
		coord_x,
		coord_y
	};

	if ((freq > 9 && freq < 101) && (freq + floor) < ch.height)
	{
		vector< vector<short> > height = vector<vector<short>>(ch.size, vector<short>(ch.size, 0));

		srand(GeneratePsuedoKey(coord_x, coord_y) * map.seed);

		height[0][0] = rand() % freq + (floor + 1);
		height[0][16] = rand() % freq + (floor + 1);
		height[16][0] = rand() % freq + (floor + 1);
		height[16][16] = rand() % freq + (floor + 1);

		height = GenerateHeightMap(coord_x, coord_y, freq, ch.size, 0, 0, height);

		memset(ch.chunk, 0, sizeof(ch.chunk));

		for (int a = 0; a < ch.size; a++)
		{
			for (int b = 0; b < ch.size; b++)
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
	throw invalid_argument("Invalid frequency value. Frequency must be between 10, and 100.");
}

/* CreateChunk(Chunk ch);
*  Description:
*  Returns:
*  Parameters:
*/
void VoxelMap::CreateChunk(Chunk ch)
{
	for (int a = 0; a < ch.size; a++)
	{
		for (int b = 0; b < ch.size; b++)
		{
			for (int c = 0; c < ch.height_map[a][b]; c++)
			{
				ch.chunk[a][b][c] = (short)1;
			}
		}
	}
}

/*
*  Description:
*  Returns:
*  Parameters:
*/
Chunk* VoxelMap::GetChunk(int grid_x, int grid_y)
{
	if ((grid_x > -1 && grid_x < map.width) && (grid_y > -1 && grid_y < map.height))
	{
		return &map.grid[grid_x][grid_y];
	}
}

/*
*  Description:
*  Returns:
*  Parameters:
*/
short VoxelMap::GetChunkValue(int grid_x, int grid_y, int chunk_x, int chunk_y, int chunk_z)
{
	if ((grid_x > -1 && grid_x < map.width) && (grid_y > -1 && grid_y < map.height))
	{
		Chunk ch = map.grid[grid_x][grid_y];

		if ((chunk_x > -1 && chunk_x < ch.size) && (chunk_y > -1 && chunk_y < ch.size))
		{
			if (chunk_z > -1 && chunk_z < ch.height)
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

/* GenerateHeightMap(int, int, string, int)
*  Description:
*  Returns: int**
*  Parameters: coord_x : Virtual coordinate X
*			   coord_y : Virtual coordinate Y
size: size of region that we're generating
TLX, TLY: top left corner coordinates for the region relative to the vector<vector<short>>
*/
vector< vector<short> > VoxelMap::GenerateHeightMap(int coord_x, int coord_y, int freq, int size, int TLX, int TLY, vector<vector<short>> height)
{
	pair<int, int> coords = MapToRealCoord(coord_x, coord_y);

	//This mess generates the middle top, middle right, middle left, middle bottom, and center values relative to the region
	height[TLX + ((size - 1) / 2)][TLY] = (height[TLX][TLY] + height[TLX + (size - 1)][TLY]) / 2; //top
	height[TLX + (size - 1)][TLY + ((size - 1) / 2)] = (height[TLX + (size - 1)][TLY] + height[TLX + (size - 1)][TLY + (size - 1)]) / 2; //right
	height[TLX][TLY + ((size - 1) / 2)] = (height[TLX][TLY] + height[TLX][TLY + (size - 1)]) / 2; //left
	height[TLX + ((size - 1) / 2)][TLY + (size - 1)] = (height[TLX][TLY + (size - 1)] + height[TLX + (size - 1)][TLY + (size - 1)]) / 2; //bottom
	height[TLX + ((size - 1) / 2)][TLY + ((size - 1) / 2)] = (height[TLX][TLY] + height[TLX + (size - 1)][TLY + (size - 1)] + height[TLX][TLY + (size - 1)] + height[TLX + (size - 1)][TLY]) / 4; //middle

	if (size > 3) //then divide into fourths and recurse
	{
		height = GenerateHeightMap(coord_x, coord_y, freq, (size + 1) / 2, TLX, TLY, height); //top left corner
		height = GenerateHeightMap(coord_x, coord_y, freq, (size + 1) / 2, TLX + ((size - 1) / 2), TLY, height); //top right corner
		height = GenerateHeightMap(coord_x, coord_y, freq, (size + 1) / 2, TLX, TLY + ((size - 1) / 2), height); //bottom left corner
		height = GenerateHeightMap(coord_x, coord_y, freq, (size + 1) / 2, TLX + ((size - 1) / 2), TLY + ((size - 1) / 2), height); //bottom left corner
	}

	return height;
}

/*
*  Description:
*  Returns:
*  Parameters:
*/
int VoxelMap::GeneratePsuedoKey(int coord_x, int coord_y)
{
	srand((u_int)(coord_x));
	srand(rand() * (u_int)(sin(coord_y) * 10 + 100));
	return rand();// *stoi(map.seed);
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
*  Description:
*  Returns:
*  Parameters:
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
	pair<int, int> coords(coord_x + map.offset_X, coord_y + map.offset_Y);
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
	pair<int, int> coords(coord_x - map.offset_X, coord_y - map.offset_Y);
	return coords;
}