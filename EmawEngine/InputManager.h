#pragma once
#include "KeyState.h"
#include "MouseState.h"

#define MOUSEBUTTON_LEFT 0
#define MOUSEBUTTON_MID 1
#define MOUSEBUTTON_RIGHT 2

// Singleton class that handles input from parsing windows messages, no async calls are used.
class InputManager
{
public:
	static InputManager* getInstance();
	void registerWindow(HWND hWnd);

	// Windows Message handlers
	void handleKeyDownMessage(WPARAM wParam);
	void handleKeyUpMessage(WPARAM wParam);
	void handleMouseDownMessage(WPARAM wParam, int id);
	void handleMouseUpMessage(WPARAM wParam, int id);
	void handleMouseMoveMessage(LPARAM lParam);

	// State checking
	bool mouseButtonDown(int button);
	bool mouseButtonClicked(int button);
	bool mouseButtonReleased(int button);
	bool keyDown(Key k);
	bool keyPressed(Key k);
	bool keyReleased(Key k);
	POINT getMousePos();
	POINT getMouseScreenPos();
	float getMousePosDiffX();
	float getMousePosDiffY();

	void update();

private:
	InputManager();
	~InputManager();
	
	HWND _hWnd;

	// Statics
	static bool instanceFlag;
	static InputManager *instance;
	
	// State objects
	MouseState* _mouseState;
	KeyState* _keyState;
};