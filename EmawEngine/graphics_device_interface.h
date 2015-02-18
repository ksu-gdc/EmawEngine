/* grahpics_device_interface. h */
#ifndef GRAPHICS_DEVICE_INTERFACE_H
#define GRAPHICS_DEVICE_INTERFACE_H

#include <d3d11.h>

/* Globals */

/* GraphicsDeviceInterface */
class GraphicsDeviceInterface
{
public: 
	GraphicsDeviceInterface();
	~GraphicsDeviceInterface();

	bool Initialize(HWND, WindowSize*);
	void Shutdown();
	void NextFrame();

private:
	bool Render();

	IDXGISwapChain			*m_Swapchain;
	ID3D11Device			*m_Device;
	ID3D11DeviceContext		*m_Context;
	ID3D11RenderTargetView  *m_BackBuffer;
};

#endif