#ifndef Helper
#define Helper
#include "resource.h"
#include "stdafx.h"
struct ShaderStruct{
	ID3D11VertexShader *VertShader;
	ID3D11PixelShader *PixShader;
	ID3D11InputLayout *InputLayout;
};

struct VERTEX
{
	FLOAT X, Y, Z;
	D3DXCOLOR Color;
};

#endif