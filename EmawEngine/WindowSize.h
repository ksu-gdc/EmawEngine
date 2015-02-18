/* WindowSize.h */
#ifndef WINDOW_SIZE_H
#define WINDOW_SIZE_H

/* Globals */
enum RES { LOW_4_3, HIGH_4_3, LOW_16_9, HIGH_16_9 };

/* WindowSize */
class WindowSize
{
public:
	WindowSize();
	~WindowSize();

	int getWidth();
	int getHeight();
	RES getResolution();
	void setSize(RES resolution);

private:
	void forceSize(RES resolution);

	int width;
	int height;
	RES resolution;
	static const int wResolution[];
	static const int hResolution[];
};

#endif