// FrameCounter.h
// James Tyson

#include <string>

class FrameCounter
{
public:
	FrameCounter();
	~FrameCounter();

	void Update();
	std::wstring GetFps();

private:
	unsigned int _fps;
	unsigned int _numFrames;
	DWORD _currentTime;
	DWORD _lastTime;
	DWORD _elapsedTime;
};