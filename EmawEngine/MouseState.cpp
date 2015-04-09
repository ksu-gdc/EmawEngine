#include "stdafx.h"
#include "MouseState.h"
#include "Windowsx.h"


MouseState::MouseState()
{
	_currentState = new bool[NUM_BUTTONS];
	_oldState = new bool[NUM_BUTTONS];
	memset(_currentState, 0, sizeof(bool) * NUM_BUTTONS);
	memset(_oldState, 0, sizeof(bool) * NUM_BUTTONS);

	_screen.x = 0;
	_screen.y = 0;
	_client.x = 0;
	_client.y = 0;

	// set cursor to sticking point
	if (!SetCursorPos(300, 300)) {
		OutputDebugString(L"failed to set cursor position.\n");
	}
}

MouseState::~MouseState()
{
	delete[] _currentState;
	delete[] _oldState;
}

// Handles a windows mouse down message and sets the appropriate flag to true
void MouseState::handleMouseDownMessage(WPARAM wParam, int button) {
	_currentState[button] = true;
}

// Handles a windows mouse up messages and sets the appropriate flag to false
void MouseState::handleMouseUpMessage(WPARAM wParam, int button) {
	_currentState[button] = false;
}

// Handles a windows mouse move message and stores the appropraite screen coordinates
void MouseState::handleMouseMoveMessage(LPARAM lParam, HWND hWnd) {
	_client.x = GET_X_LPARAM(lParam);
	_client.y = GET_Y_LPARAM(lParam);
	_screen.x = _client.x;
	_screen.y = _client.y;
	ClientToScreen(hWnd, &_screen);
}

// Copies the current state into the old state
void MouseState::update() {
	std::copy(_currentState, _currentState + sizeof(bool) * NUM_BUTTONS, _oldState);
}

// Returns trye if the specified mouse button is down
bool MouseState::mouseButtonDown(int button) {
	bool down = false;
	if (_currentState[button])
		down = true;
	return down;
}

// Returns true if the mouse button was up last update call, and down the current update call
bool MouseState::mouseButtonClicked(int button) {
	bool clicked = false;
	if (!_oldState[button] && _currentState[button])
		clicked = true;
	return clicked;
}

// Returns true if the specified mouse button is up
bool MouseState::mouseButtonReleased(int button) {
	bool released = false;
	if (_oldState[button] && !_currentState[button])
		released = true;
	return released;
}

// Gets the mouse position in client coordinates
POINT MouseState::getMousePos() {
	return _client;
}

// Gets the moue position in screen coordinates
POINT MouseState::getMouseScreenPos() {
	return _screen;
}