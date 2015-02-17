#include "stdafx.h"
#include "WindowSize.h"


WindowSize::WindowSize()
{
	this->setSize(800, 600);
}

int WindowSize::getWidth()
{
	return width;
}

int WindowSize::getHeight()
{
	return height;
}

void WindowSize::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

WindowSize::~WindowSize()
{
}
