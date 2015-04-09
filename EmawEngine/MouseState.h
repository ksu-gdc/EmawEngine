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
	void centerMouse(HWND hWnd);
	void lockMouse(HWND hWnd);
	void unlockMouse();
	// Methods that get the state
	bool mouseButtonDown(int button);
	bool mouseButtonClicked(int button);
	bool mouseButtonReleased(int button);
	POINT getMouseDelta();
	POINT getMousePos();
	POINT getMouseScreenPos();


private:
	bool *_currentState;
	bool *_oldState;
	bool _locked;
	POINT _screen;
	POINT _client;
	POINT _delta;
};


