#pragma once
#include "KeyState.h"
#include "MouseState.h"

#define MOUSEBUTTON_LEFT 0
#define MOUSEBUTTON_MID 1
#define MOUSEBUTTON_RIGHT 2

// Singleton class that handles input from parsign windows messages, no async calls are used.
class InputManager
{
public:
	static InputManager* getInstance();
	// State accessors
	KeyState* getKeyState();
	MouseState* getMouseState();
	// Windows Message handlers
	void handleKeyDownMessage(WPARAM wParam);
	void handleKeyUpMessage(WPARAM wParam);
	void handleMouseDownMessage(WPARAM wParam, int id);
	void handleMouseUpMessage(WPARAM wParam, int id);

	void update();

private:
	InputManager();
	~InputManager();
	// Statics
	static bool instanceFlag;
	static InputManager *instance;
	// State objects
	MouseState* _mouseState;
	KeyState* _keyState;
};