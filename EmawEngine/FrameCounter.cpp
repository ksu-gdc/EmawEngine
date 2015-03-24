// FrameCounter.cpp
// James Tyson

#include "stdafx.h"
#include "FrameCounter.h"
#include <string>

// Default Constructor
FrameCounter::FrameCounter() {
	fps = 0;
	numFrames = 0;
	currentTime = 0;
	lastTime = 0;
	elapsedTime = 0;
}

// Update runs each loop, adding the new frame to the number of frames and resets every second
void FrameCounter::Update() {
	// Increment the number of frames
	numFrames++;
	// Get our elapsed time since the last call
	currentTime = GetTickCount();
	elapsedTime = currentTime - lastTime;
	// Store and reset our values for the next second
	if (elapsedTime >= 1000) {
		fps = numFrames;
		lastTime = currentTime;
		numFrames = 0;
	}
}

// Get the fps value
std::wstring FrameCounter::GetFps() {
	std::string s = std::to_string(fps);
	std::wstring stemp = std::wstring(s.begin(), s.end());
	return stemp;
}

// Default Destructor
FrameCounter::~FrameCounter() {

}