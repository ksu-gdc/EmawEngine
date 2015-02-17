/* WindowSize.h */
#ifndef WINDOW_SIZE_H
#define WINDOW_SIZE_H

/* Globals */

/* WindowSize */
class WindowSize
{
public:
	WindowSize();
	~WindowSize();

	int getWidth();
	int getHeight();
	void setSize(int width, int height);

private:
	int width;
	int height;
};

#endif