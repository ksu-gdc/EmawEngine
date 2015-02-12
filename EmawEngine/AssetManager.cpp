#include "stdafx.h"
#include "AssetManager.h"
#include "Asset.h"
#include <hash_map>


AssetManager::AssetManager()
{
	typedef std::pair< std::string, std::string > AssetPair;

	dictionary.insert(AssetPair("Test", "1"));
	dictionary.insert(AssetPair("Testt", "2"));
	dictionary.insert(AssetPair("Testtt", "3"));
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

// Print out our dictionary into the std::cout
void AssetManager::printDictionary() {
	stdext::hash_map< std::string, std::string  >::iterator iter;
	for (iter = dictionary.begin(); iter != dictionary.end(); iter++)
	{
		std::string test = iter->first;
		std::string test1 = iter->second;
	}
}