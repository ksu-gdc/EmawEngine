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
	_keyState = new KeyState();
	_mouseState = new MouseState();
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

// Handles a windows mouse up message
void InputManager::handleMouseUpMessage(WPARAM wParam, int id) {
	_mouseState->handleMouseUpMessage(wParam, id);
}

void InputManager::handleMouseMoveMessage(LPARAM lParam) {
	_mouseState->handleMouseMoveMessage(lParam);
}


bool InputManager::mouseButtonDown(int button) {
	return _mouseState->mouseButtonDown(button);
}


bool InputManager::mouseButtonClicked(int button) {
	return _mouseState->mouseButtonClicked(button);
}


bool InputManager::mouseButtonReleased(int button) {
	return _mouseState->mouseButtonReleased(button);
}


bool InputManager::keyDown(Key k) {
	return _keyState->keyDown(k);
}


bool InputManager::keyPressed(Key k) {
	return _keyState->keyPressed(k);
}


bool InputManager::keyReleased(Key k) {
	return _keyState->keyReleased(k);
}