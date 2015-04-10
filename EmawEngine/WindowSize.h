/* WindowSize.h */
#ifndef WINDOW_SIZE_H
#define WINDOW_SIZE_H

/* forward declaractions */
class GraphicsDeviceInterface;

/* Globals */
enum RES { LOW_4_3, HIGH_4_3, LOW_16_9, HIGH_16_9 }; // holds supported resolutions

/* WindowSize */
class WindowSize
{
public:
	WindowSize();
	~WindowSize();

	int getWidth();
	int getHeight();
	RES getResolution();
	void setSize(HWND, GraphicsDeviceInterface*, RES);

private:
	void forceSize(RES);

	int width;
	int height;
	RES resolution;
	static const int wResolution[];
	static const int hResolution[];
};

#endif