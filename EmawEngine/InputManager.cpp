#include "stdafx.h"
#include "InputManager.h"


// Returns the instance of our AssetManager
InputManager* InputManager::getInstance() {
	if (!instanceFlag)
	{
		instance = new InputManager();
		instanceFlag = true;
	}
	return instance;
}


InputManager::InputManager() 
{
}

InputManager::~InputManager()
{
}
