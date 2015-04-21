#ifndef Helper
#define Helper
#include "resource.h"
#include "stdafx.h"
#include <DirectXMath.h>
#include <d3dx10math.h>


struct Vector {
	float x;
	float y;
	float z;
};

struct ShaderStruct{
	ID3D11VertexShader *VertShader;
	ID3D11PixelShader *PixShader;
	ID3D11GeometryShader *GeoShader;
	ID3D11InputLayout *InputLayout;
};

struct MatrixBuffer
{
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
};

struct VERTEX
{
	FLOAT X, Y, Z, W;
	DirectX::XMFLOAT4 Color;
};

enum SHADERTYPE
{
	GEO,
	COL,
	TEX
};

#endif