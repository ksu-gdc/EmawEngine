#ifndef Helper
#define Helper
#include "resource.h"
#include "stdafx.h"
#include <DirectXMath.h>

struct ShaderStruct{
	ID3D11VertexShader *VertShader;
	ID3D11PixelShader *PixShader;
	ID3D11InputLayout *InputLayout;
};

struct VERTEX
{
	FLOAT X, Y, Z;
	DirectX::XMFLOAT4 Color;
};

#endif