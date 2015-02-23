<<<<<<< HEAD
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
=======
#pragma once
#include <map>;
#include "Asset.h"
class AssetManager
{
private:
	AssetManager();
	~AssetManager();
	// Statics
	static bool instanceFlag;
	static AssetManager *instance;

	// Storage
	std::map <std::string, Asset*> assets;
	std::string rootAssetFolder;

	// Loading
	Asset* loadFromFile(std::string);
	Asset* loadTexture(std::string);
	Asset* loadShader(std::string);
	Asset* loadMusic(std::string);
	Asset* loadSoundFX(std::string);
	Asset* loadVoxelMap(std::string);
	Asset* loadBSPMap(std::string);

	// Unloading
	void unloadTexture(std::string);
	void unloadShader(std::string);
	void unloadMusic(std::string);
	void unloadSoundFX(std::string);
	void unloadVoxelMap(std::string);
	void unloadBSPMap(std::string);

public:
	static AssetManager* getInstance();
	void setRootFolder(std::string path);
	Asset* load(std::string name);
	void unloadAsset(std::string name);
>>>>>>> origin/assetmanager
};