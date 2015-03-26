#pragma once
#define NUM_BUTTONS 3

class MouseState
{
public:
	MouseState();
	~MouseState();
	// Methods that handle changes in state
	void handleMouseDownMessage(WPARAM wParam, int button);
	void handleMouseUpMessage(WPARAM wParam, int button);
	void update();
	// Methods that get the state
	bool mouseButtonClicked(int button);
	bool mouseButtonDown(int button);
	bool mouseButtonUp(int button);


private:
	bool _currentState[NUM_BUTTONS];
	bool _oldState[NUM_BUTTONS];
};


