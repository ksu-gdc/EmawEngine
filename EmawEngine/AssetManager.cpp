#include "stdafx.h"
#include "AssetManager.h"
#include <hash_map>
#include <fstream>

bool AssetManager::instanceFlag = false;
AssetManager* AssetManager::instance = NULL;

AssetManager::AssetManager()
{
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
		Asset *asset;
		assets[name] = loadFromFile(name);
		return asset;
	}
}

// Checks for and then loads a file
Asset* AssetManager::loadFromFile(std::string name) {
	Asset* asset;

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
Asset* AssetManager::loadTexture(std::string) {
	Asset* asset;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadTexture(std::string) {
	//TODO: Unload asset
}

// Shaders ====================================
Asset* AssetManager::loadShader(std::string) {
	Asset* asset;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadShader(std::string) {
	//TODO: Unload asset
}

// Music ====================================
Asset* AssetManager::loadMusic(std::string) {
	Asset* asset;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadMusic(std::string) {
	//TODO: Unload asset
}

// SoundFX ====================================
Asset* AssetManager::loadSoundFX(std::string) {
	Asset* asset;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadSoundFX(std::string) {
	//TODO: Unload asset
}

// VoxelMap ====================================
Asset* AssetManager::loadVoxelMap(std::string) {
	Asset* asset;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadVoxelMap(std::string) {
	//TODO: Unload asset
}

// BSPMap ====================================
Asset* AssetManager::loadBSPMap(std::string) {
	Asset* asset;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadBSPMap(std::string) {
	//TODO: Unload asset
}