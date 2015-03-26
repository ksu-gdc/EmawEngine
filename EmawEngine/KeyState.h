#pragma once
#define NUM_KEYS 256

enum Key {
	// Escape
	Esc = 0x1B,

	// Function keys
	F1 = 0x70,
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

	// PrintScreen
	PrintScreen = 0x2C,

	// Arrow Keys
	Left = 0x25,
	Up,
	Right,
	Down,

	// Number row
	Num_0 = 0x30,
	Num_1,
	Num_2,
	Num_3,
	Num_4,
	Num_5,
	Num_6,
	Num_7,
	Num_8,
	Num_9,

	// Numpad
	NumPad_0 = 0x60,
	Numpad_1,
	Numpad_2,
	Numpad_3,
	Numpad_4,
	Numpad_5,
	Numpad_6,
	Numpad_7,
	Numpad_8,
	Numpad_9,

	// Enter
	Enter = 0x0D,

	// Backspace/Tab
	BackSpace = 0x08,
	Tab,

	// CapsLock
	CapsLock = 0x14,

	// Shift/Ctrl/Alt
	Shift = 0x10,
	Ctrl,
	Alt,

	// Letters
	A = 0x41,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,

	// Windows Keys
	LWin = 0x5B,
	RWin,

	// OEM
	Semicolon = 0xBA,
	Plus,
	Comma,
	Minus,
	Period,
	Slash,
	Tilda,

	// More OEM
	LeftSquareBracket = 0xDB,
	Backslash,
	RightSquareBracket,

	// Shifts
	LShift = 0xA0,
	RShift,

	// Space
	Space = 0x20,
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
};



