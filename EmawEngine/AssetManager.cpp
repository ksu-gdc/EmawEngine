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
TDSFX* AssetManager::load3D(string name, Position* position, FMOD::System *system){
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

		name = "3d_" + name;
		TDSFX *sound2 = new TDSFX(name, sound, position);
		sounds[name] = sound2;
	}

	return (TDSFX*)sounds.find(name)->second;
}

//Get character's actual position
Position* AssetManager::getCharactersActualPosition(){
	return actualPos;
}

//Get character's last position
Position* AssetManager::getCharactersLastPosition(){
	return lastPos;
}

//Set character's actual position
bool AssetManager::setCharactersActualPosition(float x, float y, float z){
	FMOD_VECTOR vel;

	if (actualPos == NULL){
		actualPos = new Position(x,y,z);
		lastPos = new Position(x, y, z);
	}
	else {
		delete lastPos;
		lastPos = actualPos;
		actualPos = new Position(x, y, z);
	}

	// vel tells how far we moved during last FRAME (m/f) with time-compensated to SECONDS (m/s).
	vel.x = (actualPos->getX() - lastPos->getX()) * (1000 / getUpdateTime());
	vel.y = (actualPos->getY() - lastPos->getY()) * (1000 / getUpdateTime());
	vel.z = (actualPos->getZ() - lastPos->getZ()) * (1000 / getUpdateTime());

	if (soundSystem == NULL){
		throw fmodex;
	}


	FMOD_RESULT result = soundSystem->set3DListenerAttributes(0, &(actualPos->getVector()), &vel, &getCharactersForwardsOrientation(), &getCharactersUpwardsOrientation());

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

//Loading of 3D SFX with looping
TDSFX* AssetManager::load3DLoop(string name, Position* position, FMOD::System *system){
	TDSFX * sound = load3D(name, position, system);

	FMOD_RESULT result = sound->sound->setMode(FMOD_LOOP_NORMAL);

	checkProblem(result);

	return sound;
}