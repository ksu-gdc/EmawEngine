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
	AssetManager();
public:
	static AssetManager* getInstance();
	void setRootFolder(std::string path);
	Asset* getAsset(std::string name);
	~AssetManager();
};