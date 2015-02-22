#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>

using namespace std;

class TextureShader
{
public:
	TextureShader();
	TextureShader(const TextureShader&);
	~TextureShader();

	bool initialize(ID3D11Device*, HWND);
	void unload();
	bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX,
		ID3D11ShaderResourceView*);

private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	bool initializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void unloadShader();
	void outputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);
	bool setShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX,
		ID3D11ShaderResourceView*);
	void RenderShader(ID3D11DeviceContext*, int);

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
};

