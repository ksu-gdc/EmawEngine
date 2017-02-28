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

struct BoxBounds {
	float top;
	float bot;
	float left;
	float right;
	float away;
	float towards;
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
	FLOAT U, V;
};

enum SHADERTYPE
{
	GEO,
	COL,
	TEX
};

#endif