/* grahpics_device_interface. h */
#ifndef GRAPHICS_DEVICE_INTERFACE_H
#define GRAPHICS_DEVICE_INTERFACE_H

#include <d3d11.h>
#include <D3DX10.h>
#include "ShaderAsset.h"
#include "VertexShader.h"
#include "GameNode.h"
#include "Camera.h"

/* Globals */

/* GraphicsDeviceInterface */
class GraphicsDeviceInterface
{
	friend class ShaderAsset;
public: 
	GraphicsDeviceInterface();
	~GraphicsDeviceInterface();

	bool Initialize(HWND, WindowSize*);
	void SetSceneGraphRoot(GameNode*);
	void SetCamera(Camera* camera);
	void Shutdown();
	void NextFrame();
	void InitPipeline();
	void InitGraphics();
	bool Update(std::vector<VERTEX>*);
	void VertexPipeline(std::vector<VERTEX>*, D3DXMATRIX*);

private:
	bool Render();
	bool RenderModel();
	void RenderShader();

	ShaderAsset				*shdrs;
	IDXGISwapChain			*m_Swapchain;
	ID3D11Device			*m_Device;
	ID3D11DeviceContext		*m_Context;
	ID3D11RenderTargetView  *m_BackBuffer;
	ID3D11Buffer			*m_VertBuffer;

	VertexShader			*m_VertexShader;
	GameNode				*m_SceneGraphRoot;
	Camera					*m_Camera;
	D3DXMATRIX				m_projMatrix;
};

#endif