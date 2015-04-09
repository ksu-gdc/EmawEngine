#include "stdafx.h"
#include "MouseState.h"
#include "Windowsx.h"


MouseState::MouseState()
{
	_currentState = new bool[NUM_BUTTONS];
	_oldState = new bool[NUM_BUTTONS];
	memset(_currentState, 0, sizeof(bool) * NUM_BUTTONS);
	memset(_oldState, 0, sizeof(bool) * NUM_BUTTONS);

	_locked = false;

	_screen.x = 0;
	_screen.y = 0;
	_client.x = 0;
	_client.y = 0;

	ShowCursor(false);
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

// Handles a windows mouse move message and stores the appropriate screen coordinates
void MouseState::handleMouseMoveMessage(LPARAM lParam, HWND hWnd) {	
	// Calculate the mouse delta
	int x = GET_X_LPARAM(lParam);
	int y = GET_Y_LPARAM(lParam);
	_delta.x += _client.x - x;
	_delta.y += _client.y - y;

	// Store the new coordinates
	_client.x = x;
	_client.y = y;
	_screen.x = _client.x;
	_screen.y = _client.y;
	ClientToScreen(hWnd, &_screen);

	// Move mouse back if we are locked
	if (_locked)
		centerMouse(hWnd);
}

// Centers the mouse to the center of the given window
void MouseState::centerMouse(HWND hWnd) {
	RECT rect;
	if (GetWindowRect(hWnd, &rect)) {
		int xMid = (rect.right - rect.left) / 2;
		int yMid = (rect.bottom - rect.top) / 2;
		SetCursorPos(xMid, yMid);
	}
}

// Locks the mouse to the center of the sreen
void MouseState::lockMouse(HWND hWnd) {
	_locked = true;
	ShowCursor(false);
	centerMouse(hWnd);
}

// Unlocks the mouse and shows the cursor
void MouseState::unlockMouse() {
	_locked = false;
	ShowCursor(true);
}

// Copies the current state into the old state
void MouseState::update() {
	std::copy(_currentState, _currentState + sizeof(bool) * NUM_BUTTONS, _oldState);
	_delta.x = 0;
	_delta.y = 0;
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

// Gets the change in the mouse position since the last update call
POINT MouseState::getMouseDelta() {
	return _delta;
}

// Gets the mouse position in client coordinates
POINT MouseState::getMousePos() {
	return _client;
}

// Gets the moue position in screen coordinates
POINT MouseState::getMouseScreenPos() {
	return _screen;
}