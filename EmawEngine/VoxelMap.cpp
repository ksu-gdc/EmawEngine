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
	try
	{
		fstream file = GetFileHandle(dir + "map.dat", ios::in);
		string line;
		//Chunk blank;

		while (getline(file, line))
		{
			vector<string> tokens = Parse(line, '=');

			if (tokens[0] == "Seed")
			{
				map.seed = tokens[1];
			}
			else if (tokens[0] == "Directory")
			{
				map.directory = tokens[1];
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

		//memset(blank.chunk, 0, sizeof(blank.chunk));
		map.offset_X = (int)floor(map.width / 2);
		map.offset_Y = (int)floor(map.height / 2);
		map.grid = vector<vector<Chunk>>(map.width, vector<Chunk>(map.height/*, blank*/));
	}
	catch (exception e) { throw e; }
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
	if (width > 0 && height > 0) {
		//Chunk blank;

		//memset(blank.chunk, 0, sizeof(blank.chunk));

		width = abs(width);
		height = abs(height);

		if ((width % 2) != 1 && width > 0) width += 1;
		if ((height % 2) != 1 && height > 0) height += 1;

		map = {
			seed,
			dir,
			width,
			height,
			(int)floor(width / 2),
			(int)floor(height / 2),
			0,
			0,
			vector<vector<Chunk>>(width, vector<Chunk>(height/*, blank*/))
		};

		MakeDirectory(map.directory);
		MakeDirectory(map.directory + "Regions/");
	}
}

/* # PUBLIC FUNCTIONS # */

/* GetMap();
*  Description: Retrieves the Grid object, and returns it.
*  Returns: Grid : Grid struct representing
*/
Grid VoxelMap::GetMap() { return map; }

/* SaveMap();
*  Description: Updates the directory's map file. Returns a bool indicating success of failure.
*  Returns: bool : Indiciates success or failure of save operation.
*/
bool VoxelMap::SaveMap()
{
	try
	{
		fstream file = GetFileHandle(map.directory + "map.dat", ios::out | ios::trunc);

		file << "Seed=" << map.seed << endl;
		file << "Directory=" << map.directory << endl;
		file << "Width=" << map.width << endl;
		file << "Height=" << map.height << endl;
		file << "Center_X=" << map.center_X << endl;
		file << "Center_Y=" << map.center_Y << endl;

		file.close();

		for (size_t a = 0; a < map.grid.size(); a++)
		{
			for (size_t b = 0; b < map.grid[a].size(); b++)
			{
				SaveChunk(map.grid[a][b]);
			}
		}

		return true;
	}
	catch (exception e) { throw e; }
}

/*
*  Description:
*  Returns:
*  Parameters:
*/
void VoxelMap::SetMapCenter(int coord_x, int coord_y)
{

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
		memset(vr.chunk, 0, sizeof(vr.chunk));

		try
		{
			string line, name = "r." + to_string(coords.first) + "." + to_string(coords.second) + ".hmap";
			fstream file = GetFileHandle(map.directory + "Regions/" + name, ios::in);

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
		catch (exception e)
		{
			//TO DO : Create variables for floor, and frequency. 
			vr = CreateChunk(coords.first, coords.second, map.seed, 10, 5);
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
	try
	{
		string name = "r." + to_string(ch.coord_X) + "." + to_string(ch.coord_Y) + ".hmap";
		fstream file = GetFileHandle(map.directory + "Regions/" + name, ios::out | ios::trunc);

		for (int a = 0; a < ch.length; a++)
		{
			file << a << "=";

			for (int b = 0; b < ch.width; b++)
			{
				file << ch.height_map[a][b];

				if (b == (ch.width - 1))
				{
					file << endl;
				}
				else
				{
					file << ",";
				}
			}
		}

		ch.set = true;
		file.close();
	}
	catch (exception e) { throw e; }
}

/* CreateChunk(int, int, string, int, int);
*  Description:
*  Returns:
*  Parameters:
*/
Chunk VoxelMap::CreateChunk(int coord_x, int coord_y, string seed, int freq, int floor)
{
	if ((freq >= 10 && freq <= 100) && (freq + floor) < map.grid[0][0].height)
	{
		vector< vector<short> > height = vector<vector<short>>(map.width, vector<short>(map.height, 0));
		height[0][0] = rand() % (freq + floor) + floor;
		height[0][17] = rand() % (freq + floor) + floor;
		height[17][0] = rand() % (freq + floor) + floor;
		height[17][17] = rand() % (freq + floor) + floor;
		height = GenerateHeightMap(coord_x, coord_y, freq, 17, 0, 0, height);

		Chunk ch = {
			coord_x,
			coord_y,
			true
		};

		memset(ch.chunk, 0, sizeof(ch.chunk));

		for (int a = 0; a < ch.length; a++)
		{
			for (int b = 0; b < ch.width; b++)
			{
				for (int c = 0; height[a][b]; c++)
				{
					ch.chunk[a][b][c] = (short)1;
				}
			}
		}

		ch.set = true;
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
	for (int a = 0; a < ch.length; a++)
	{
		for (int b = 0; b < ch.width; b++)
		{
			for (int c = 0; c < ch.height_map[a][b]; c++)
			{
				ch.chunk[a][b][c] = (short)1;
			}
		}
	}

	ch.set = true;
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
		height = GenerateHeightMap(coord_x, coord_y, freq, (size + 1)/2, TLX, TLY, height); //top left corner
		height = GenerateHeightMap(coord_x, coord_y, freq, (size + 1) / 2, TLX + ((size - 1) /2) , TLY, height); //top right corner
		height = GenerateHeightMap(coord_x, coord_y, freq, (size + 1) / 2, TLX, TLY + ((size - 1) /2), height); //bottom left corner
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
	return rand();
}

/*
*  Description:
*  Returns:
*  Parameters:
*/
bool VoxelMap::IsChunkAdjacent(int coord_x, int coord_y, Adjacent side)
{
	pair<int, int> coords = MapToRealCoord(coord_x, coord_y);

	switch (side)
	{
	case LEFT:
		if (coords.second >= 0 && coords.second <= 14)
		{
			if ((coords.first - 1) >= 0 && (coords.first - 1) < 14)
			{
				if (map.grid[coords.first - 1][coords.second].set == true)
				{
					return true;
				}
			}
		}
		return false;
	case RIGHT:
		if (coords.second >= 0 && coords.second <= 14)
		{
			if ((coords.first + 1) > 0 && (coords.first + 1) <= 14)
			{
				if (map.grid[coords.first + 1][coords.second].set == true)
				{
					return true;
				}
			}
		}
		return false;
	case TOP:
		if (coords.first >= 0 && coords.first <= 14)
		{
			if ((coords.second - 1) >= 0 && (coords.second - 1) < 14)
			{
				if (map.grid[coords.first][coords.second - 1].set == true)
				{
					return true;
				}
			}
		}
		return false;
	case BOTTOM:
		if (coords.first >= 0 && coords.first <= 14)
		{
			if ((coords.first + 1) > 0 && (coords.first + 1) <= 14)
			{
				if (map.grid[coords.first + 1][coords.second].set == true)
				{
					return true;
				}
			}
		}
		return false;
	default:
		return false;
	}
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