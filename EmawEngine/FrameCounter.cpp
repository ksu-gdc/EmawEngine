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
	lastFrameTime = 0;
	elapsedFrameTime = 0;
	elapsedTime = 0;
}

// Update runs each loop, adding the new frame to the number of frames and resets every second
void FrameCounter::Update() {
	// Increment the number of frames
	numFrames++;
	// Get our elapsed time since the last call
	currentTime = GetTickCount();
	elapsedFrameTime = currentTime - lastFrameTime;
	lastFrameTime = currentTime;
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

// Get the elapsedTime value in string form (duh)
std::wstring FrameCounter::GetElapsedString()
{
	std::string s = std::to_string(elapsedTime);
	std::wstring stemp = std::wstring(s.begin(), s.end());
	return stemp;
}

// Get the elapsedFrameTime value in string form (duh)
std::wstring FrameCounter::GetElapsedFrameString()
{
	std::string s = std::to_string(elapsedFrameTime);
	std::wstring stemp = std::wstring(s.begin(), s.end());
	return stemp;
}

// Get the elapsedTime value (duh)
DWORD FrameCounter::GetElapsedTime()
{
	return elapsedTime;
}

// Get the elapsedTime value (duh)
DWORD FrameCounter::GetElapsedFrameTime()
{
	return elapsedFrameTime;
}

// Default Destructor
FrameCounter::~FrameCounter() {

}