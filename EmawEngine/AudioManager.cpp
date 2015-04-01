//AssetManager for sound library
//Author: Ondrej Kuzela

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include "AudioManager.h"

using namespace std;

bool AudioManager::instanceFlag = false;
AudioManager* AudioManager::instance = NULL;

AudioManager::AudioManager()
{
}


//Destructor for clearing maps
AudioManager::~AudioManager(){
	for (map<string, Sound*>::iterator it = sounds.begin(); it != sounds.end(); ++it){
		delete it->second;
	}
	sounds.clear();
	filenames.clear();
}

// Returns the instance of our AssetManager
AudioManager* AudioManager::getInstance() {
	if (!instanceFlag)
	{
		instance = new AudioManager();
		instanceFlag = true;
	}
	return instance;
}

//Method for loading sounds
//If sound is not loaded into map, then its object is created and saved into map.
//Sound's object is loaded from map and returned.
Sound* AudioManager::load(string name, FMOD::System *system){
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
bool AudioManager::add(string name, string filename){
	filenames[name] = filename;
	return true;
}

//Method for loading 3D SFX
TDSFX* AudioManager::load3D(string filename, string name, Position* position, FMOD::System *system){
	FMOD::Sound *sound;

	FMOD_RESULT result = system->createSound(filename.c_str(), FMOD_3D, 0, &sound);

	checkProblem(result);

	result = sound->set3DMinMaxDistance(0.5f * DISTANCE_FACTOR, 5000.0f * DISTANCE_FACTOR);

	checkProblem(result);

	TDSFX *sound2 = new TDSFX(name, sound, position);

	return sound2;
}

//Get character's actual position
Position* AudioManager::getCharactersActualPosition(){
	return actualPos;
}

//Get character's last position
Position* AudioManager::getCharactersLastPosition(){
	return lastPos;
}

//Set character's actual position
bool AudioManager::setCharactersActualPosition(float x, float y, float z){
	FMOD_VECTOR vel;

	if (actualPos == NULL){
		actualPos = new Position(x, y, z);
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
FMOD_VECTOR AudioManager::getCharactersForwardsOrientation(){
	return FORWARD_ORIENTATION;
}

//Get character's upwards orientation
//Test implementation, needs to be implemented
FMOD_VECTOR AudioManager::getCharactersUpwardsOrientation(){
	return UP_ORIENTATION;
}

//Get update time
//Test implementation, needs to be implemented
int AudioManager::getUpdateTime(){
	return UPDATE_TIME;
}

//Set sound system
bool AudioManager::setSoundSystem(FMOD::System *system){
	soundSystem = system;
	return true;
}

//Loading of 3D SFX with looping
TDSFX* AudioManager::load3DLoop(string filename, string name, Position* position, FMOD::System *system){
	TDSFX * sound = load3D(filename, name, position, system);

	FMOD_RESULT result = sound->sound->setMode(FMOD_LOOP_NORMAL);

	checkProblem(result);

	return sound;
}