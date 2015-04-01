#include "stdafx.h"
#include "KeyState.h"

// Default constructor
KeyState::KeyState()
{
	_currentState = new bool[NUM_KEYS];
	_oldState = new bool[NUM_KEYS];
	memset(_currentState, 0, sizeof(bool) * NUM_KEYS);
	memset(_oldState, 0, sizeof(bool) * NUM_KEYS);
}

// Default destructor
KeyState::~KeyState()
{
	delete[] _currentState;
	delete[] _oldState;
}

// Handles a windoes key down message
void KeyState::handleKeyDownMessage(WPARAM wParam) {
	_currentState[wParam] = true;
}

// Handles a windows key up message
void KeyState::handleKeyUpMessage(WPARAM wParam) {
	_currentState[wParam] = false;
}

// Copies the current state into the old state
void KeyState::update() {
	std::copy(_currentState, _currentState + sizeof(bool) * NUM_KEYS, _oldState);
}

// Returns true if the specified key is down
bool KeyState::keyDown(Key k) {
	bool down = false;
	if (_currentState[(int)k])
		down = true;
	return down;
}

// Returns true if the key was up last update call, and down the current update call
bool KeyState::keyPressed(Key k) {
	bool pressed = false;
	int keyCode = (int)k;
	if (!_oldState[keyCode] && _currentState[keyCode])
		pressed = true;
	return pressed;
}

// Returns true if the key was down last update call, and up the current update call
bool KeyState::keyReleased(Key k) {
	bool released = false;
	int keyCode = (int)k;
	if (_oldState[keyCode] && !_currentState[keyCode])
		released = true;
	return released;
}