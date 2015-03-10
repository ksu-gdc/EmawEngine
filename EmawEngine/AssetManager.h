#pragma once
#include <map>
#include "Asset.h"
class AssetManager
{
private:
	AssetManager(GraphicsDeviceInterface *device);
	~AssetManager();
	// Statics
	static bool instanceFlag;
	static AssetManager *instance;
	static GraphicsDeviceInterface *graphicsDevice;

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
};