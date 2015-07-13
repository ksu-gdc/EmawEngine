#include "stdafx.h"
#include "AssetManager.h"
#include <hash_map>
#include <fstream>

bool AssetManager::instanceFlag = false;
AssetManager* AssetManager::instance = NULL;
GraphicsDeviceInterface* AssetManager::graphicsDevice = NULL;

AssetManager::AssetManager()
{
	rootAssetFolder = "";
}


AssetManager::~AssetManager()
{
}

// Sets the asset managers reference to the graphics device.  This needs to happen during initialization
void AssetManager::setGraphicsDevice(GraphicsDeviceInterface *device) {
	graphicsDevice = device;
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
		asset = assets[name];
		return asset;
	}
}

// Checks for and then loads a file
Asset* AssetManager::loadFromFile(std::string name) {
	Asset* asset = NULL;
	name =  name;
	// Check if the file exists
	if (std::ifstream(name).good()) {
		// Get the extension and call the appropraite method
		std::string ext = name.substr(name.size() - 3);

		if (ext == "png" || ext == "jpeg")
			asset = loadTexture(name);
		else if (ext == "wav" || ext == "mp3")
			asset = loadMusic(name);
		else if (ext == "geo" || ext == "col" || ext == "tex")
			asset = loadShader(name);
		else
			
			(L"File type not supported.");
	}
	else {
		OutputDebugString(L"File not found.\n");
	}

	return asset;
}

// Textures ====================================
Asset* AssetManager::loadTexture(std::string name) {
	Texture texture(NULL); // TODO: figure out what parameter should go in here
	texture.load(name);
	return &texture;
}
void AssetManager::unloadTexture(std::string name) {
	char *cstr = &name[0u];
	Texture* model = (Texture*)assets[cstr];
	model->unload();
}

// Models ======================================
Asset* AssetManager::loadModel(std::string name) {
	Model model;
	model.load(name);
	return &model;
}
void AssetManager::unloadModel(std::string name) {
	char *cstr = &name[0u];
	Model* model = (Model*)assets[cstr];
	model->unload();
}

// Shaders ====================================
Asset* AssetManager::loadShader(std::string name) {
	// Shaders require a reference to the graphics device
	ShaderAsset* shader = new ShaderAsset(graphicsDevice);
	shader->load(name);
	return shader;
}
void AssetManager::unloadShader(std::string name) {
	char *cstr = &name[0u];
	ShaderAsset* shader = (ShaderAsset*)assets[cstr];
	shader->unload();
}

// Fonts ======================================
Asset* AssetManager::loadFont(std::string name) {
	Font font;
	font.load(name);
	load(font.getFontPngPath());
	return &font;
}
void AssetManager::unloadFont(std::string name) {
	char *cstr = &name[0u];
	Font* font = (Font*)assets[cstr];
	font->unload();
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
/*Asset* AssetManager::loadVoxelMap(std::string name) {
	VoxelMap voxmap(name);
	//TODO: Load asset
	return &voxmap;
}
void AssetManager::unloadVoxelMap(std::string name) {
	//TODO: Unload asset
}*/

// BSPMap ====================================
Asset* AssetManager::loadBSPMap(std::string name) {
	Asset* asset = NULL;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadBSPMap(std::string name) {
	//TODO: Unload asset

}