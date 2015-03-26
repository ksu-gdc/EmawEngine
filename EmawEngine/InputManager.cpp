#include "stdafx.h"
#include "InputManager.h"

bool InputManager::instanceFlag = false;
InputManager* InputManager::instance = NULL;
// Returns the instance of our AssetManager
InputManager* InputManager::getInstance() {
	if (!instanceFlag)
	{
		instance = new InputManager();
		instanceFlag = true;
	}
	return instance;
}

// Default constructor
InputManager::InputManager() 
{
	_keyState = &(KeyState());
	_mouseState = &(MouseState());
}

// Default destructor
InputManager::~InputManager()
{
}

// Updates the mouse and key states
void InputManager::update() {
	_mouseState->update();
	_keyState->update();
}

// Handles a windows key down message
void InputManager::handleKeyDownMessage(WPARAM wParam) {
	_keyState->handleKeyDownMessage(wParam);
}

// Handles a windows key up message
void InputManager::handleKeyUpMessage(WPARAM wParam) {
	_keyState->handleKeyUpMessage(wParam);
}

// Handles a windows key down message
void InputManager::handleMouseDownMessage(WPARAM wParam, int id) {
	_mouseState->handleMouseDownMessage(wParam, id);
}

// Handles a windoes mouse up message
void InputManager::handleMouseUpMessage(WPARAM wParam, int id) {
	_mouseState->handleMouseUpMessage(wParam, id);
}

// Returns the current key state
KeyState* InputManager::getKeyState() {
	return _keyState;
}

// Returns the current mouse state
MouseState* InputManager::getMouseState() {
	return _mouseState;
}