/* grahpics_device_interface. h */
#ifndef GRAPHICS_DEVICE_INTERFACE_H
#define GRAPHICS_DEVICE_INTERFACE_H

#include <d3d11.h>
#include "ShaderAsset.h"

/* Globals */

/* GraphicsDeviceInterface */
class GraphicsDeviceInterface
{
	friend class ShaderAsset;
public: 
	GraphicsDeviceInterface();
	~GraphicsDeviceInterface();

	bool Initialize(HWND, WindowSize*);
	void Shutdown();
	void NextFrame();
	void InitPipeline();
	void InitGraphics();
	bool Update(std::vector<VERTEX>*);

private:
	bool Render();

	ShaderAsset				*shdrs;
	IDXGISwapChain			*m_Swapchain;
	ID3D11Device			*m_Device;
	ID3D11DeviceContext		*m_Context;
	ID3D11RenderTargetView  *m_BackBuffer;
	ID3D11Buffer			*m_VertBuffer;
};

#endif