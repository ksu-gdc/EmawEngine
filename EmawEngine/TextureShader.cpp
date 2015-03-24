#include "stdafx.h"
#include "TextureShader.h"


/*
* Constructor just initializes variables to 0.
*/
TextureShader::TextureShader()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
	m_sampleState = 0;
}


TextureShader::~TextureShader()
{
}


bool TextureShader::initialize(ID3D11Device* device, HWND hwnd, WCHAR* vPath, WCHAR* pPath)
{
	bool result;
	result = initializeShader(device, hwnd, vPath, pPath);
	if (!result)
		return false;
	return true;
}

/*
* Calls the release of the shader variables
*/
void TextureShader::unload()
{
	unloadShader();
	return;
}

/*
* Takes a pointer to a texture resource.  Then sent into the SetShaderParameters Function
* so that the texture can be set in the shader and then used for rendering
*/
bool TextureShader::Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix,
	D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	bool result;

	//set shader parameters
	result = setShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)
		return false;

	//render the prepared buffers with the shader
	RenderShader(deviceContext, indexCount);
	return true;
}


/*
* Sets up the texture shader
*/
bool TextureShader::initializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;

	//Initialize the pointers to null.
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	//Load in the new texture vertex and pixel shaders

	//Compile the vertex shader code
	result = D3DX11CompileFromFile(vsFilename, NULL, NULL, "TextureVertexShader", "vs_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);

	if (FAILED(result))
	{
		if (errorMessage)
			outputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		else
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		return false;
	}

	//Compile the pixel shader code
	result = D3DX11CompileFromFile(psFilename, NULL, NULL, "TexturePixelShader", "ps_5_0", 
		D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);

	if (FAILED(result))
	{
		if (errorMessage)
			outputShaderErrorMessage(errorMessage, hwnd, psFilename);
		else
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		return false;
	}

	//Create the vertex shader from the buffer
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result))
		return false;

	//Create the pixel shader from the buffer
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result))
		return false;

	//Create the vertex layout description
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	//Get count of elements in the layout
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	//Create the vertex input layout
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
		return false;

	//Release buffers as they are no longer needed.
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;
	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	//Setup the descriptino of the dynamic matrix constant buffer that is in the vertex shader
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
		return false;

	//Create a texture sampler state description
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//Create the texture sampler state
	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
		return false;
	return true;
}


/*
* Function to release the new sampler state that was created during initialization
*/
void TextureShader::unloadShader()
{
	//Release the sampler state
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	//Release the matrix buffer
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	//Release the layout
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	//Release the pixel shader
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	//Release the vertex shader
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}

	return;
}


/*
* Writes out errors to a text file if the HLSL shader could not be loaded 
*/
void TextureShader::outputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, 
	WCHAR* shaderFilename)
{
	char* errors;
	unsigned long bufferSize;
	unsigned long i;
	ofstream fout;

	//Get pointer to the error message text buffer and length of message
	errors = (char*)(errorMessage->GetBufferPointer());
	bufferSize = errorMessage->GetBufferSize();

	//Open a file to write error message to, then write out error message and close the file.
	fout.open("shader-error.txt");
	for (i = 0; i < bufferSize; i++)
	{
		fout << errors[i];
	}
	fout.close();

	//Release the error message
	errorMessage->Release();
	errorMessage = 0;

	//Notify the user the check the error file.
	MessageBox(hwnd, L"Error compiling shader. Check shader-error.txt for message",
		shaderFilename, MB_OK);

	return;
}


/*
* Takes in a pointer to a texture resource and then assigns it to the shader using the 
* texture resource pointer.  The texture has to be set before rendering the buffer.
*/
bool TextureShader::setShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, 
	D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;

	//Transpose the matrices.
	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

	//Lock the constant buffer so it can be written to
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
		return false;

	//Obtain a pointer to the data in the constant buffer and copy the matrices.
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	//Unlock the buffer and set the position
	deviceContext->Unmap(m_matrixBuffer, 0);
	bufferNumber = 0;

	//Set the buffer in the vertex shader with the updated values  and set 
	//the shader texture resource in the pixel shader
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);
	deviceContext->PSGetShaderResources(0, 1, &texture);
	return true;
}


/*
* Calls the sahder technique to render the polygons
*/
void TextureShader::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(m_layout);
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);
	deviceContext->PSSetSamplers(0, 1, &m_sampleState);
	deviceContext->DrawIndexed(indexCount, 0, 0);
	return;
}