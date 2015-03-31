#include "stdafx.h"
#include "graphics_device_interface.h"
#include "Font.h"

//#include <DirectXColors.h>
#include <DirectXMath.h>

#define _XM_NO_INTRINSICS_

GraphicsDeviceInterface::GraphicsDeviceInterface() {
}

GraphicsDeviceInterface::~GraphicsDeviceInterface() {}

//
// FUNCTION: GraphicsDeviceInterface::Initialize()
//
// PURPOSE: Initializes Direct3D
// 
bool GraphicsDeviceInterface::Initialize(HWND hWnd, WindowSize* wind) {
	HRESULT hResult;

	// Clear the struct
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// Set the swap chain values
	scd.BufferCount = 1;								// one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// use 32 bit color
	scd.BufferDesc.Width = wind->getWidth();			// set width using windowSize object
	scd.BufferDesc.Height = wind->getHeight();			// set height using windowSize object
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// swap chain is output
	scd.OutputWindow = hWnd;							// window to render into
	scd.SampleDesc.Count = 4;							// use 4 multisamples for antialiasing
	scd.Windowed = wind->getWindowed();					// Sets windowed mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	// Allow full-screen switching

	// Create the device, context, and swap chain
	hResult = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL, //D3D_FEATURE_LEVEL_10_0,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&m_Swapchain,
		&m_Device,
		NULL,
		&m_Context);

	if (hResult != S_OK)
	{
		return FALSE;
	}

	// Retrieves the IDXGIFactory that created "m_Device"
	IDXGIDevice *pDXGIDevice;
	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);
	IDXGIAdapter *pDXGIAdapter;
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);
	IDXGIFactory *pDXGIFactory;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&pDXGIFactory);

	// Disables the use of Alt-Enter to switch between fullscreen/windowed
	pDXGIFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);
	
	// Resized the target (window or screen resolution) and back buffers
	m_Swapchain->ResizeTarget(&scd.BufferDesc);
	m_Swapchain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, scd.Flags);

	// Get the back buffer address
	ID3D11Texture1D *pBackBuffer;
	m_Swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// Use the back buffer address to create a render target
	m_Device->CreateRenderTargetView(pBackBuffer, NULL, &m_BackBuffer);
	pBackBuffer->Release();

	// set the render target as the back buffer
	m_Context->OMSetRenderTargets(1, &m_BackBuffer, NULL);

	// Set the viewport using windowSize object
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)wind->getWidth();
	viewport.Height = (float)wind->getHeight();

	m_Context->RSSetViewports(1, &viewport);

	InitPipeline();
	InitGraphics();

	return TRUE;
}

//Placeholder used for testing, loads the shaders into the Graphics Device Context.
void GraphicsDeviceInterface::InitPipeline()
{
	//load shaders
	shdrs = new ShaderAsset(this);
	ShaderStruct *blah = (ShaderStruct*)shdrs->load("Shaders.col");

	m_Context->VSSetShader(blah->VertShader, 0, 0);
	m_Context->PSSetShader(blah->PixShader, 0, 0);
//	m_Context->GSSetShader(blah->GeoShader, 0, 0);

	m_Context->IASetInputLayout(blah->InputLayout);
}

//Placeholder used for testing, manually creates a triangle and sends the vertices for the Graphics Device for rendering.
void GraphicsDeviceInterface::InitGraphics(void)
{
	//the triangle
	VERTEX OurVertices[] = {
			{ 0.0f, 0.0f, 1.0f, 0.5f, DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ 1.0f, 0.0f, 1.0f, 0.5f, DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ -1.0f, 0.0f, 1.0f, 0.5f, DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
	};
	Entity* e = new Entity();

	//TEST CODE
	Font* f = new Font();
	f->load("B:/consolas.fnt");

	Model *m = f->createFontModel("Hello!", 0, 0, 0, NULL, 0.005);

	std::vector<VERTEX> vertices = e->getModel()->getVertexBuffer();
	vertices = m->getVertexBuffer();

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
	bd.ByteWidth = sizeof(VERTEX) * vertices.size();             // size is the VERTEX struct * 3
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

	m_Device->CreateBuffer(&bd, NULL, &m_VertBuffer);       // create the buffer

	D3D11_MAPPED_SUBRESOURCE ms;
	m_Context->Map(m_VertBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);   // map the buffer
	memcpy(ms.pData, vertices.data(), vertices.size() * sizeof(VERTEX));                // copy the data
	m_Context->Unmap(m_VertBuffer, NULL);
}

//
// FUNCTION: GraphicsDeviceInterface::Shutdown()
//
// PURPOSE: Releases all resources held by the GraphicsDeviceInterface
// 
void GraphicsDeviceInterface::Shutdown() {

	m_Swapchain->SetFullscreenState(FALSE, NULL);	// switch to windowed mode

	// close and release all COM objects
	m_Swapchain->Release();
	m_BackBuffer->Release();
	m_Device->Release();
	m_Context->Release();
	m_VertBuffer->Release();
}


//
// FUNCTION: GraphicsDeviceInterface::NextFrame()
//
// PURPOSE: Prepares the next frame to be rendered to screen
//
void GraphicsDeviceInterface::NextFrame()
{
	Render();
}

//
// FUNCTION: GraphicsDeviceInterface::IsWindowed()
//
// PURPOSE: returns false if fullscreen, true if windowed;
//
BOOL GraphicsDeviceInterface::IsWindowed()
{
	if (m_Swapchain == NULL) // this occurs when program is starting up
		return TRUE;

	BOOL fullscreen;
	m_Swapchain->GetFullscreenState(&fullscreen, NULL);

	return !fullscreen;
}

//
// FUNCTION: GraphicsDeviceInterface::Render()
//
// PURPOSE: Renders the next frame
//
bool GraphicsDeviceInterface::Render()
{
	// Default color
	float color[4] = { 0.2, 0.11, 0.34, 1.0 };
	
	// Clear the back buffer
	m_Context->ClearRenderTargetView(m_BackBuffer, color);

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	m_Context->IASetVertexBuffers(0, 1, &m_VertBuffer, &stride, &offset);

	// select which primtive type we are using
	m_Context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw the vertex buffer to the back buffer
	m_Context->Draw(36, 0);

	// TODO: Clear the depth buffer

	// TODO: Render game world

	// Swap buffers - waits for vsync
	//m_Swapchain->Present(1, 0);

	// Swap buffers - unlocked framerate
	m_Swapchain->Present(0, 0);

	return true;
}