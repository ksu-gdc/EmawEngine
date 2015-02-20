#include "stdafx.h"
#include "ShaderAsset.h"
#include "graphics_device_interface.h"

/*
 * Construtor requires the GraphicsDeviceInterface to be passed in as it's required for loading the shader.
 */
ShaderAsset::ShaderAsset(void *gdi)
{
	gInterface = gdi;
	ZeroMemory(&Shaders, sizeof(Shaders));
}


ShaderAsset::~ShaderAsset()
{
}

/*
 * Parameters: the file name of the text file that contains the shader to be loaded.
 * Output: A ShaderStruct contaning a vertex shader, a pixel shader, and the input layout for the Graphics Card.
 * What it does: loads a vertex shader and a pixel shader and returns them in a struct.
 */
void* ShaderAsset::load(char* filename)
{
	//convert to wchar
	size_t size = strlen(filename) + 1;
	size_t convertedChars = 0;
	wchar_t wcstring[100];
	mbstowcs_s(&convertedChars, wcstring, size, filename, size-1);
	//load shaders
	ID3DBlob *VS, *PS;
	D3DCompileFromFile(wcstring, 0, 0, "VShader", "vs_4_0", 0, 0, &VS, 0);
	D3DCompileFromFile(wcstring, 0, 0, "PShader", "ps_4_0", 0, 0, &PS, 0);


	GraphicsDeviceInterface* Interface = (GraphicsDeviceInterface*)gInterface;
	Interface->m_Device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &Shaders.VertShader);
	Interface->m_Device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &Shaders.PixShader);

	D3D11_INPUT_ELEMENT_DESC ied[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	Interface->m_Device->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &Shaders.InputLayout);
	return &Shaders;
}

//take a guess.
void* ShaderAsset::getData()
{
	return &Shaders;
}

//guess.
bool ShaderAsset::unload()
{
	Shaders.InputLayout->Release();
	Shaders.PixShader->Release();
	Shaders.VertShader->Release();
	return true;
}