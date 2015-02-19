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
	unsigned int fps;
	unsigned int numFrames;
	DWORD currentTime;
	DWORD lastTime;
	DWORD elapsedTime;
};