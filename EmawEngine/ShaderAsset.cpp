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
	unload();
}

/*
 * Parameters: the file name of the text file that contains the shader to be loaded.
 * Output: A ShaderStruct contaning a vertex shader, a pixel shader, and the input layout for the Graphics Card.
 * What it does: loads a vertex shader and a pixel shader and returns them in a struct.
 */
void* ShaderAsset::load(std::string str)
{
	char *filename = &str[0u];

	//get filetype
	int type = getShaderType(filename);
	//convert to wchar
	size_t size = strlen(filename) + 1;
	size_t convertedChars = 0;
	wchar_t wcstring[100];
	mbstowcs_s(&convertedChars, wcstring, size, filename, size - 1);
	//load shaders
	ID3DBlob *VS, *PS, *GS, *err;
	HRESULT otherErr;
	otherErr = D3DCompileFromFile(wcstring, 0, 0, "VShader", "vs_4_0", 0, 0, &VS, &err);
	if (otherErr != S_OK) {
		OutputDebugString(L"vertex shader failed to compile.\n");
		return NULL;
	}
	otherErr = D3DCompileFromFile(wcstring, 0, 0, "PShader", "ps_4_0", 0, 0, &PS, 0);
	if (otherErr != S_OK) {
		OutputDebugString(L"pixel shader failed to compile.\n");
		return NULL;
	}
	if (type == GEO) D3DCompileFromFile(wcstring, 0, 0, "GShader", "gs_4_0", D3DCOMPILE_DEBUG, 0, &GS, &err);

	GraphicsDeviceInterface* Interface = (GraphicsDeviceInterface*)gInterface;
	Interface->m_Device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &Shaders.VertShader);
	Interface->m_Device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &Shaders.PixShader);
	if (type == GEO) otherErr = Interface->m_Device->CreateGeometryShader(GS->GetBufferPointer(), GS->GetBufferSize(), NULL, &Shaders.GeoShader);

	// changes to this structure must be reflected in the call to CreateInputLayout;
	// the second parameter must equal the number of elements
	D3D11_INPUT_ELEMENT_DESC ied[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	Interface->m_Device->CreateInputLayout(ied, 3, VS->GetBufferPointer(), VS->GetBufferSize(), &Shaders.InputLayout);

	
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
	Shaders.GeoShader->Release();
	Shaders.PixShader->Release();
	Shaders.VertShader->Release();
	return true;
}

int	ShaderAsset::getShaderType(char* filename)
{
	char namecopy[100];
	strcpy(namecopy, filename);
	char* name = strtok(namecopy, ".");
	char* suffix = strtok(NULL, ".");

	if (strcmp(suffix, "geo") == 0) return GEO;
	else if (strcmp(suffix, "col") == 0) return COL;
	else if (strcmp(suffix, "tex") == 0) return TEX;
}