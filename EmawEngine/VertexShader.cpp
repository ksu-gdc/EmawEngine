#include "stdafx.h"
#include "VertexShader.h"

VertexShader::VertexShader(){
	m_vertexShader = 0;
}

VertexShader::~VertexShader(){

}

bool VertexShader::initializeShader(ID3D11Device* device){

	// create a buffer in graphics memory to transfer the transformation matricies to the vertex shader
	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBuffer);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	HRESULT result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result)) {
		OutputDebugString(L"failed to create transform matrix buffer\n");
		return false;
	}

	return true;
}

bool VertexShader::setParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX w, D3DXMATRIX v, D3DXMATRIX p){

	HRESULT result;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result)) {
		OutputDebugString(L"failed to map transform matrix buffer\n");
		return false;
	}

	MatrixBuffer* mb = (MatrixBuffer*)mappedResource.pData;

	mb->world = w;
	mb->view = v;
	mb->projection = p;

	deviceContext->Unmap(m_matrixBuffer, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &m_matrixBuffer);
	m_matrixBuffer->Release();

	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result)) {
		OutputDebugString(L"failed to map transform matrix buffer\n");
		return false;
	}

	mb = (MatrixBuffer*)mappedResource.pData;

	mb->world = w;
	mb->view = v;
	mb->projection = p;

	deviceContext->Unmap(m_matrixBuffer, 0);
	deviceContext->GSSetConstantBuffers(0, 1, &m_matrixBuffer);
	m_matrixBuffer->Release();

	return true;

}