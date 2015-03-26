#pragma once
#include "KeyState.h"
#include "MouseState.h"

#define MOUSEID_LEFT 0
#define MOUSEID_MID 1
#define MOUSEID_RIGHT 2

class InputManager
{
public:
	static InputManager* getInstance();

	KeyState* getKeyState();
	MouseState* getMouseState();

	void handleKeyDownMessage(WPARAM wParam);
	void handleKeyUpMessage(WPARAM wParam);
	void handleMouseDownMessage(WPARAM wParam, int id);
	void handleMouseUpMessage(WPARAM wParam, int id);

private:
	InputManager();
	~InputManager();
	// Statics
	static bool instanceFlag;
	static InputManager *instance;
};