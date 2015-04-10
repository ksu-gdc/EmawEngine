#include "stdafx.h"
#include "InputManager.h"

// Initialize our singleton variables
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

void InputManager::registerWindow(HWND hWnd) {
	_hWnd = hWnd;
}

// Default destructor
InputManager::~InputManager()
{
	delete _keyState;
	delete _mouseState;
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

// Handles a windoes mouse move message
void InputManager::handleMouseMoveMessage(LPARAM lParam) {
	_mouseState->handleMouseMoveMessage(lParam, _hWnd);
}

// Asks the mouse state if a given mouse button is down
bool InputManager::mouseButtonDown(int button) {
	return _mouseState->mouseButtonDown(button);
}

// Asks the mouse state if a given mouse button has been clicked since the last update call
bool InputManager::mouseButtonClicked(int button) {
	return _mouseState->mouseButtonClicked(button);
}

// Asks the mouse state if a give mouse state has been released since the last update call
bool InputManager::mouseButtonReleased(int button) {
	return _mouseState->mouseButtonReleased(button);
}

// Asks the key state if a given key is down
bool InputManager::keyDown(Key k) {
	return _keyState->keyDown(k);
}

// Asks the key state if a given key has been pressed since the last update call
bool InputManager::keyPressed(Key k) {
	return _keyState->keyPressed(k);
}

// Asks the key state if a given key has been released since the last update call
bool InputManager::keyReleased(Key k) {
	return _keyState->keyReleased(k);
}

// Gets the current mouse position in client coordinates
POINT InputManager::getMousePos() {
	return _mouseState->getMousePos();
}

// Gets the current mouse position in screen coordinates
POINT InputManager::getMouseScreenPos() {
	return _mouseState->getMouseScreenPos();
}

// Gets the mouse delta since the last update call
POINT InputManager::getMouseDelta() {
	return _mouseState->getMouseDelta();
}

// Locks the mouse to the center of the screen and hides the cursor
void InputManager::lockMouse() {
	_mouseState->lockMouse(_hWnd);
}

// Unlocks the mosue from the center of the sreen and shows the cursor
void InputManager::unlockMouse() {
	_mouseState->unlockMouse();
}