#include "stdafx.h"
#include "WindowSize.h"

// supported resolution heights and widths
const int WindowSize::wResolution[] = { 800, 1280,	1024,	1600 };
const int WindowSize::hResolution[] = { 600, 960,	576,	900 };

WindowSize::WindowSize()
{
	this->forceSize(HIGH_16_9);
	windowed = TRUE;
}

#pragma region getters/setters
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

BOOL WindowSize::getWindowed()
{
	return windowed;
}
#pragma endregion contains get/set functions for variables


//
//   FUNCTION: setSize(HWND hWnd, GraphicsDeviceInterface *gdi, RES resolution)
//
//   PURPOSE: public function that changes the resolution when needed.
//
void WindowSize::setSize(HWND hWnd, GraphicsDeviceInterface *gdi, RES resolution)
{
	// Update resolution width and height
	forceSize(resolution);

	// Shutdown and reinitialize graphics device interface
	gdi->Shutdown();
	gdi->Initialize(hWnd, this);
}

//
//   FUNCTION: forceSize(RES resolution)
//
//   PURPOSE: private function that changes the object fields when needed.
//
void WindowSize::forceSize(RES resolution)
{
	this->width = wResolution[resolution];
	this->height = hResolution[resolution];
	this->resolution = resolution;
}

WindowSize::~WindowSize()
{
}
