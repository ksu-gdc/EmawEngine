//AssetManager for sound library
//Author: Ondrej Kuzela

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include "AssetManager.h"

using namespace std;

//Method for loading sounds
//If sound is not loaded into map, then its object is created and saved into map.
//Sound's object is loaded from map and returned.
Sound* AssetManager::load(string name, FMOD::System *system){
	if (sounds.find(name) == sounds.end()){
		FMOD::Sound *sound;

		const char* filename = NULL;

		if (filenames.find(name) != filenames.end()){
			filename = (filenames.find(name)->second).c_str();
		}
		else {
			throw fmodex;
		}

		FMOD_RESULT result = system->createSound(filename, FMOD_DEFAULT, 0, &sound);

		checkProblem(result);

		Sound *sound2 = new Sound(name, sound);
		sounds[name] = sound2;
	}

	return sounds.find(name)->second;
}

//Method for adding filename to filename's map
bool AssetManager::add(string name, string filename){
	filenames[name] = filename;
	return true;
}

//Destructor for clearing maps
AssetManager::~AssetManager(){
	for (map<string, Sound*>::iterator it = sounds.begin(); it != sounds.end(); ++it){
		delete it->second;
	}
	sounds.clear();
	filenames.clear();
}