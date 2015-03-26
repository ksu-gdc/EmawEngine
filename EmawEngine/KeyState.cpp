#include "stdafx.h"
#include "KeyState.h"


KeyState::KeyState()
{
	// Ensure zeroed out memory at start up
	memset(_currentState, 0, sizeof(_currentState));
	memset(_oldState, 0, sizeof(_oldState));
}


KeyState::~KeyState()
{
}

void KeyState::handleKeyDownMessage(WPARAM wParam) {
	_currentState[wParam] = true;
}

void KeyState::handleKeyUpMessage(WPARAM wParam) {
	_currentState[wParam] = false;
}

void KeyState::update() {
	// Copy the new state into the old state
	std::copy(std::begin(_currentState), std::end(_currentState), std::begin(_oldState));
}

bool KeyState::keyPressed(Key k) {
	return false;
}

bool KeyState::keyDown(Key k) {
	return false;
}

bool KeyState::keyUp(Key k) {
	return false;
}