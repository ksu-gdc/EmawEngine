#pragma once
#include <map>
#include "Asset.h"
#include "Font.h"
class AssetManager
{
private:
	AssetManager();
	~AssetManager();
	// Statics
	static bool instanceFlag;
	static AssetManager *instance;
	static GraphicsDeviceInterface *graphicsDevice;

	void setGraphicsDevice(GraphicsDeviceInterface* device);

	// Storage
	std::map <std::string, Asset*> assets;
	std::string rootAssetFolder;

	// Loading
	Asset* loadFromFile(std::string);
	Asset* loadTexture(std::string);
	Asset* loadModel(std::string);
	Asset* loadShader(std::string);
	Asset* loadFont(std::string);
	Asset* loadMusic(std::string);
	Asset* loadSoundFX(std::string);
	Asset* loadVoxelMap(std::string);
	Asset* loadBSPMap(std::string);

	// Unloading
	void unloadTexture(std::string);
	void unloadModel(std::string);
	void unloadShader(std::string);
	void unloadFont(std::string);
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