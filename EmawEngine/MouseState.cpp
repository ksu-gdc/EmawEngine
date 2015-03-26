#include "stdafx.h"
#include "MouseState.h"


MouseState::MouseState()
{
	// Ensure zeroed out memory at start up
	memset(_currentState, 0, sizeof(_currentState));
	memset(_oldState, 0, sizeof(_oldState));
}

MouseState::~MouseState()
{
}

// Handles a windows mouse down message and sets the appropriate flag to true;
void MouseState::handleMouseDownMessage(WPARAM wParam, int button) {
	_currentState[button] = true;
}

// Handles a windows mouse up messages and sets the appropriate flag to false;
void MouseState::handleMouseUpMessage(WPARAM wParam, int button) {
	_currentState[button] = false;
}

void MouseState::update() {
	// Copy the new state into the old state
	std::copy(std::begin(_currentState), std::end(_currentState), std::begin(_oldState));
}

// Returns true if the mouse button was up last update call, and down the current update call
bool MouseState::mouseButtonClicked(int button) {
	bool clicked = false;
	if (!_oldState[button] && _currentState[button])
		clicked = true;
	return clicked;
}

// Returns trye if the specified mouse button is down
bool MouseState::mouseButtonDown(int button) {
	bool down = false;
	if (_currentState[button])
		down = true;
	return down;
}

// Returns true if the specified mouse button is up
bool MouseState::mouseButtonUp(int button) {
	bool up = false;
	if (!_currentState[button])
		up = true;
	return up;
}