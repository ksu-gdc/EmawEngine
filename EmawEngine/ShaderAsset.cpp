#include "stdafx.h"
#include "ShaderAsset.h"
#include "graphics_device_interface.h"

ShaderAsset::ShaderAsset(GraphicsDeviceInterface *gdi)
{
	gInterface = gdi;
	ZeroMemory(&Shaders, sizeof(Shaders));
}


ShaderAsset::~ShaderAsset()
{
}

void* ShaderAsset::load(char* filename)
{
	//convert to wchar
	size_t size = strlen(filename) + 1;
	size_t convertedChars = 0;
	wchar_t wcstring[100];
	mbstowcs_s(&convertedChars, wcstring, size, filename, size-1);
	//load shaders
	ID3D10Blob *VS, *PS;
	D3DX11CompileFromFile(wcstring, 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
	D3DX11CompileFromFile(wcstring, 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);


//	GraphicsDeviceInterface* gInterface = (GraphicsDeviceInterface*)gInterface;
	gInterface->m_Device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &Shaders.VertShader);
	gInterface->m_Device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &Shaders.PixShader);

	D3D11_INPUT_ELEMENT_DESC ied[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	gInterface->m_Device->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &Shaders.InputLayout);
	return &Shaders;
}

void* ShaderAsset::getData()
{
	return &Shaders;
}

bool ShaderAsset::unload()
{
	Shaders.InputLayout->Release();
	Shaders.PixShader->Release();
	Shaders.VertShader->Release();
	return true;
}