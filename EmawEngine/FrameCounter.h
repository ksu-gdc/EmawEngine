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
	std::wstring GetElapsedString();
	std::wstring GetElapsedFrameString();
	DWORD GetElapsedTime();
	DWORD GetElapsedFrameTime();

private:
	unsigned int fps;
	unsigned int numFrames;
	DWORD currentTime;
	DWORD lastTime;
	DWORD lastFrameTime;
	DWORD elapsedFrameTime;
	DWORD elapsedTime;
};