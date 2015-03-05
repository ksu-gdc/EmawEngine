//AssetManager for sound library
//Author: Ondrej Kuzela

#pragma once
#include <string>
#include <map>
#include "Sound.h"
#include "fmod/fmod.hpp"
#include "Utils.h"
#include "TDSFX.h"
#include "Position.h"

class AssetManager {
private:
	//map codenames -> filenames
	map<string, string> filenames;

	//map codenames -> sound objects
	map<string, Sound*> sounds;

	//FMOD System
	FMOD::System *soundSystem = NULL;

	//character's position
	Position* actualPos = NULL;
	Position* lastPos = NULL;

public:
	~AssetManager();

	//Method for loading Sound
	Sound* load(string name, FMOD::System *system);

	//Method for loading 3D SFX
	TDSFX* load3D(string name, Position* position, FMOD::System *system);

	//Method for loading 3D SFX with looping
	TDSFX* load3DLoop(string name, Position* position, FMOD::System *system);

	//Method for adding filename to filename's map
	bool add(string name, string filename);

	//Get character's actual position
	Position* getCharactersActualPosition();
	
	//Get character's last position
	Position* getCharactersLastPosition();

	//Set character's actual position
	bool setCharactersActualPosition(float x, float y, float z);

	//Get character's forwards orientation
	FMOD_VECTOR getCharactersForwardsOrientation();

	//Get character's upwards orientation
	FMOD_VECTOR getCharactersUpwardsOrientation();

	//Get update time
	int getUpdateTime();

	//Set sound system
	bool setSoundSystem(FMOD::System *system);
};