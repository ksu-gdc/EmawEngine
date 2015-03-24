#include "stdafx.h"
#include "WindowSize.h"

// supported resolution heights and widths
const int WindowSize::wResolution[] = { 800, 1280,	1024,	1600 };
const int WindowSize::hResolution[] = { 600, 960,	576,	900 };

WindowSize::WindowSize()
{
	this->forceSize(HIGH_16_9);
	windowed = FALSE;
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
	/*
	// Check to see resolution needs to be changed
	if (this->resolution != resolution || this->windowed != gdi->IsWindowed())
	{
		// save fullscreen state
		BOOL fullscreen = !gdi->IsWindowed();
		
		// changes width and height
		forceSize(resolution);

		// release old gdi resources
		gdi->Shutdown();

		// create adjusted rectangle for window sizing
		RECT wr = { 0, 0, width, height };
		AdjustWindowRect(&wr, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, FALSE);

		// change window size
		SetWindowPos(hWnd,
			NULL,
			0, 0,
			wr.right - wr.left,
			wr.bottom - wr.top,
			SWP_NOMOVE);

		// reinitialize resources
		gdi->Initialize(hWnd, this);

		// switch to fullscreen if needed
		if (fullscreen)
			gdi->SetFullScreenState(fullscreen);
	}
	*/
	this->windowed = gdi->IsWindowed();
	
	forceSize(resolution);

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
