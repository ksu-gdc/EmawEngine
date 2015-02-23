//AssetManager for sound library
//Author: Ondrej Kuzela

#pragma once
#include <string>
#include <map>
#include "Sound.h"
#include "fmod/fmod.hpp"
#include "Utils.h"

class AssetManager {
private:
	//map codenames -> filenames
	map<string, string> filenames;

	//map codenames -> sound objects
	map<string, Sound*> sounds;
public:
	~AssetManager();

	//Method for loading Sound
	Sound* load(string name, FMOD::System *system);

	//Method for adding filename to filename's map
	bool add(string name, string filename);
};