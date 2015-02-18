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

void WindowSize::setSize(HWND hWnd, GraphicsDeviceInterface *gdi, RES resolution)
{
	if (this->resolution != resolution)
	{
		forceSize(resolution);

		gdi->Shutdown();

		RECT wr = { 0, 0, width, height };
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

		SetWindowPos(hWnd,
			NULL,
			0, 0,
			wr.right - wr.left,
			wr.bottom - wr.top,
			SWP_NOMOVE);

		gdi->Initialize(hWnd, this);
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
