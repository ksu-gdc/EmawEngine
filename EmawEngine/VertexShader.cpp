#include "stdafx.h"
#include "VertexShader.h"

VertexShader::VertexShader(){
	m_vertexShader = 0;
}

VertexShader::~VertexShader(){

}

bool VertexShader::initializeShader(ID3D11Device* device){

	D3D11_BUFFER_DESC matrixBufferDesc;

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(TransformBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);

	return true;
}

bool VertexShader::setParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX w, D3DXMATRIX v, D3DXMATRIX p){

	HRESULT hr;

	D3D11_MAPPED_SUBRESOURCE subresource;
	TransformBufferType* dataPtr;
	unsigned int bufferNumber;

	// Transpose the matrices to prepare them for the shader.
	D3DXMatrixTranspose(&w, &w);
	D3DXMatrixTranspose(&v, &v);
	D3DXMatrixTranspose(&p, &p);

	// Lock m_matrixBuffer.
	hr = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource);

	dataPtr = (TransformBufferType*)subresource.pData;

	dataPtr->world = w;
	dataPtr->view = v;
	dataPtr->projection = p;

	// Unlock m_matrixBuffer.
	deviceContext->Unmap(m_matrixBuffer, 0);

	bufferNumber = 0;
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	return true;

}