// FrameCounter.cpp
// James Tyson

#include "stdafx.h"
#include "FrameCounter.h"
#include <string>

// Default Constructor
FrameCounter::FrameCounter() {
	_fps = 0;
	_numFrames = 0;
	_currentTime = 0;
	_lastTime = 0;
	_elapsedTime = 0;
}

// Update runs each loop, adding the new frame to the number of frames and resets every second
void FrameCounter::Update() {
	// Increment the number of frames
	_numFrames++;
	// Get our elapsed time since the last call
	_currentTime = GetTickCount();
	_elapsedTime = _currentTime - _lastTime;
	// Store and reset our values for the next second
	if (_elapsedTime >= 1000) {
		_fps = _numFrames;
		_lastTime = _currentTime;
		_numFrames = 0;
	}
}

// Get the fps value
std::wstring FrameCounter::GetFps() {
	std::string s = std::to_string(_fps);
	std::wstring stemp = std::wstring(s.begin(), s.end());
	return stemp;
}

// Default Destructor
FrameCounter::~FrameCounter() {

}