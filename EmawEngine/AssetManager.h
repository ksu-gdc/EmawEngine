#pragma once

class AssetManager
{
private:
	static bool instanceFlag;
	static AssetManager *instance;
	AssetManager();
public:
	static AssetManager* getInstance();
	void printDictionary();
	~AssetManager();
};