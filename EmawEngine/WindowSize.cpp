#include "stdafx.h"
#include "WindowSize.h"


const int WindowSize::wResolution[] = { 800,	1280,	1024,	1600 };
const int WindowSize::hResolution[] = { 600,	960,	576,	900 };

WindowSize::WindowSize()
{
	this->forceSize(LOW_4_3);
}

#pragma region getters
int WindowSize::getWidth()
{
	return width;
}

int WindowSize::getHeight()
{
	return height;
}

RES WindowSize::getResolution()
{
	return resolution;
}
#pragma endregion contains get functions for variables

void WindowSize::setSize(RES resolution)
{
	if (this->resolution != resolution)
	{
		forceSize(resolution);
	}
}

void WindowSize::forceSize(RES resolution)
{
	this->width = wResolution[resolution];
	this->height = hResolution[resolution];
	this->resolution = resolution;
}

WindowSize::~WindowSize()
{
}
