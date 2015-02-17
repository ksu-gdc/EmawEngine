#include "stdafx.h"
#include "AssetManager.h"
#include <hash_map>

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
template<typename T>
Asset* AssetManager::getAsset(std::string name) {
	if (assets[name] != nullptr) {
		return assets[name];
	}
	else {
		Asset *asset;
		assets[name] = asset;
		return asset;
	}
}

