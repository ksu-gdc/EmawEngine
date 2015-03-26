#include "stdafx.h"
#include "KeyState.h"


KeyState::KeyState()
{
}


KeyState::~KeyState()
{
}

void KeyState::update() {
	memset(_currentState, sizeof(_currentState), 0);
}

bool KeyState::keyPressed(Key k) {

}

bool KeyState::keyDown(Key k) {

}

bool KeyState::keyUp(Key k) {

}