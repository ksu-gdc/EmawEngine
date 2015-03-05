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

		FMOD_RESULT result = system->createSound(filename, FMOD_2D, 0, &sound);

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

//Method for loading 3D SFX
Sound* AssetManager::load3D(string name, FMOD::System *system){
	name = "3d_" + name;
	if (sounds.find(name) == sounds.end()){
		FMOD::Sound *sound;

		const char* filename = NULL;

		if (filenames.find(name) != filenames.end()){
			filename = (filenames.find(name)->second).c_str();
		}
		else {
			throw fmodex;
		}

		FMOD_RESULT result = system->createSound(filename, FMOD_3D, 0, &sound);

		checkProblem(result);

		result = sound->set3DMinMaxDistance(0.5f * DISTANCE_FACTOR, 5000.0f * DISTANCE_FACTOR);

		checkProblem(result);

		Sound *sound2 = new Sound(name, sound);
		sounds[name] = sound2;
	}

	return sounds.find(name)->second;
}

//Get character's actual position
FMOD_VECTOR AssetManager::getCharactersActualPosition(){
	return actualPos;
}

//Get character's last position
FMOD_VECTOR AssetManager::getCharactersLastPosition(){
	return lastPos;
}

//Set character's actual position
bool AssetManager::setCharactersActualPosition(float x, float y, float z){
	FMOD_VECTOR vel;

	lastPos = actualPos;

	actualPos = {x, y, z};

	// vel tells how far we moved during last FRAME (m/f) with time-compensated to SECONDS (m/s).
	vel.x = (actualPos.x - lastPos.x) * (1000 / getUpdateTime());
	vel.y = (actualPos.y - lastPos.y) * (1000 / getUpdateTime());
	vel.z = (actualPos.z - lastPos.z) * (1000 / getUpdateTime());

	if (soundSystem == NULL){
		throw fmodex;
	}

	FMOD_RESULT result = soundSystem->set3DListenerAttributes(0, &actualPos, &vel, &getCharactersForwardsOrientation(), &getCharactersUpwardsOrientation());

	checkProblem(result);

	result = soundSystem->update();

	checkProblem(result);

	return true;
}

//Get character's forwards orientation
//Test implementation, needs to be implemented
FMOD_VECTOR AssetManager::getCharactersForwardsOrientation(){
	return FORWARD_ORIENTATION;
}

//Get character's upwards orientation
//Test implementation, needs to be implemented
FMOD_VECTOR AssetManager::getCharactersUpwardsOrientation(){
	return UP_ORIENTATION;
}

//Get update time
//Test implementation, needs to be implemented
int AssetManager::getUpdateTime(){
	return UPDATE_TIME;
}

//Set sound system
bool AssetManager::setSoundSystem(FMOD::System *system){
	soundSystem = system;
	return true;
}