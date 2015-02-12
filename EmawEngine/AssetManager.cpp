#include "stdafx.h"
#include "AssetManager.h"
#include "Asset.h"
#include <hash_map>


AssetManager::AssetManager()
{
	typedef std::pair< std::string, std::string > AssetPair;
	stdext::hash_map< std::string, std::string > Dictionary;

	Dictionary.insert(AssetPair("Test", "1"));
	Dictionary.insert(AssetPair("Testt", "2"));
	Dictionary.insert(AssetPair("Testtt", "3"));
}


AssetManager::~AssetManager()
{
}

bool AssetManager::instanceFlag = false;
AssetManager* AssetManager::instance = NULL;
// Returns the instance of our AssetManager
AssetManager* AssetManager::getInstance()
{
	if (!instanceFlag)
	{
		instance = new AssetManager();
		instanceFlag = true;
	}
	return instance;
}

void AssetManager::printDictionary() {

}