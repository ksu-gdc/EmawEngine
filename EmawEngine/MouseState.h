#pragma once
#define NUM_BUTTONS 3

// MouseState represents the current state of the mouse buttons
class MouseState
{
public:
	MouseState();
	~MouseState();
	// Methods that handle changes in state
	void handleMouseDownMessage(WPARAM wParam, int button);
	void handleMouseUpMessage(WPARAM wParam, int button);
	void handleMouseMoveMessage(LPARAM lParam, HWND hWnd);
	void update();
	// Methods that get the state
	bool mouseButtonDown(int button);
	bool mouseButtonClicked(int button);
	bool mouseButtonReleased(int button);
	POINT getMousePos();
	POINT getMouseScreenPos();


private:
	bool *_currentState;
	bool *_oldState;
	POINT _screen;
	POINT _client;
};


