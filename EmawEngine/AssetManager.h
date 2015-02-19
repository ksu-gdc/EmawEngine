#pragma once
#include <map>;
#include "Asset.h"
class AssetManager
{
private:
	static bool instanceFlag;
	static AssetManager *instance;

	std::map <std::string, Asset*> assets;
	std::string rootAssetFolder;

	Asset* loadFromFile(std::string);
	Asset* loadTexture(std::string);
	Asset* loadShader(std::string);
	Asset* loadMusic(std::string);
	Asset* loadSoundFX(std::string);
	Asset* loadVoxelMap(std::string);
	Asset* loadBSPMap(std::string);

	AssetManager();
public:
	static AssetManager* getInstance();
	void setRootFolder(std::string path);
	Asset* getAsset(std::string name);
	~AssetManager();
};