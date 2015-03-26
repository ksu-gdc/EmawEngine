#pragma once

#define NUM_KEYS 74

enum Key {
	Esc,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	PrintScreen,
	Up,
	Left,
	Down,
	Right,
	Tilda,
	Num_1,
	Num_2,
	Num_3,
	Num_4,
	Num_5,
	Num_6,
	Num_7,
	Num_8,
	Num_9,
	Num_0,
	Dash,
	Equals,
	BackSpace,
	Tab,
	CapsLock,
	LShift,
	LCtrl,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	LeftSquareBracket,
	RightSquareBracket,
	Backslash,
	A,
	S,
	D,
	F,
	G,
	H,
	K,
	L,
	Semicolon,
	Apostrophe,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,
	Comma,
	Period,
	Slash,
	RShift,
	Windows,
	LAlt,
	RAlt,
	RControl
};

class KeyState
{
public:
	KeyState();
	~KeyState();
	// Methods that handle changes in state
	void handleKeyDownMessage(WPARAM wParam);
	void handleKeyUpMessage(WPARAM wParam);
	void update();
	// Methods that get the state
	bool keyPressed(Key k);
	bool keyDown(Key k);
	bool keyUp(Key k);


private:
	bool _currentState[NUM_KEYS];
	bool _oldState[NUM_KEYS];

	void swapState();
};



