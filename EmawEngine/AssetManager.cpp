<<<<<<< HEAD
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
=======
#include "stdafx.h"
#include "AssetManager.h"
#include <hash_map>
#include <fstream>

bool AssetManager::instanceFlag = false;
AssetManager* AssetManager::instance = NULL;

AssetManager::AssetManager()
{
	rootAssetFolder = "C:\\Users";
}


AssetManager::~AssetManager()
{
}

// Returns the instance of our AssetManager
AssetManager* AssetManager::getInstance() {
	if (!instanceFlag)
	{
		instance = new AssetManager();
		instanceFlag = true;
	}
	return instance;
}

// Sets the root folder for the assets
void AssetManager::setRootFolder(std::string path) {
	rootAssetFolder = path;
}

// Checks for an asset (loads if not found) and then returns a pointer to it
Asset* AssetManager::load(std::string name) {

	if (assets[name] != nullptr) {
		return assets[name];
	}
	else {
		Asset *asset = NULL;
		assets[name] = loadFromFile(name);
		return asset;
	}
}

// Checks for and then loads a file
Asset* AssetManager::loadFromFile(std::string name) {
	Asset* asset = NULL;
	name = rootAssetFolder + "\\" + name;
	// Check if the file exists
	if (std::ifstream(name).good()) {
		// Get the extension and call the appropraite method
		std::string ext = name.substr(name.size() - 3);

		if (ext == "pmg" || ext == "jpeg")
			loadTexture(name);
		else if (ext == "wav" || ext == "mp3")
			loadMusic(name);
		else
			OutputDebugString(L"File type not supported.");
	}
	else {
		OutputDebugString(L"File not found.\n");
	}

	return asset;
}

// Textures ====================================
Asset* AssetManager::loadTexture(std::string name) {
	Asset* asset = NULL;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadTexture(std::string name) {
	//TODO: Unload asset
}

// Shaders ====================================
Asset* AssetManager::loadShader(std::string name) {
	Asset* asset = NULL;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadShader(std::string name) {
	//TODO: Unload asset
}

// Music ====================================
Asset* AssetManager::loadMusic(std::string name) {
	Asset* asset = NULL;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadMusic(std::string name) {
	//TODO: Unload asset
}

// SoundFX ====================================
Asset* AssetManager::loadSoundFX(std::string name) {
	Asset* asset = NULL;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadSoundFX(std::string name) {
	//TODO: Unload asset
}

// VoxelMap ====================================
Asset* AssetManager::loadVoxelMap(std::string name) {
	Asset* asset = NULL;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadVoxelMap(std::string name) {
	//TODO: Unload asset
}

// BSPMap ====================================
Asset* AssetManager::loadBSPMap(std::string name) {
	Asset* asset = NULL;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadBSPMap(std::string name) {
	//TODO: Unload asset
>>>>>>> origin/assetmanager
}