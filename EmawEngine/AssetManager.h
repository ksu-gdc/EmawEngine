#pragma once
#include <hash_map>;
class AssetManager
{
private:
	static bool instanceFlag;
	static AssetManager *instance;
	stdext::hash_map< std::string, std::string > dictionary;
	AssetManager();
public:
	static AssetManager* getInstance();
	void printDictionary();
	~AssetManager();
};