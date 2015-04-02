#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>

class VertexShader {

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11Buffer* m_matrixBuffer;

public:
	VertexShader();
	~VertexShader();

	bool initializeShader(ID3D11Device*);
	bool setParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);

};