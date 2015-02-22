#include "stdafx.h"
#include "TextureManager.h"


using namespace std;


TextureManager::TextureManager()
{
	m_texture = 0;
}

TextureManager::TextureManager(const TextureManager& other)
{

}


TextureManager::~TextureManager()
{

}


/*
* initialize takes in a Direct3D Device and a file name of the texture and then
* loads the texture file into the shader resource variable m_textures.
* The texture can now be used to render with.
*
* @param device		The Direct3D device
* @param filename	The name of the file we are loading
*
* @return true if the file loaded, false otherwise
*/
bool TextureManager::initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;

	//Load texture
	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, NULL);
	if (FAILED(result))
		return false;
	return true;
}


/*
* The unload function releasee the texture resource if it has been loaded and then 
* sets the pointer to null (0)
*/
void TextureManager::unload()
{
	//Release the texture resource
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
	return;
}


/*
* Function called by other objects that need access to the texture shader resource
* so that they can use the texture for rendering.
*/
ID3D11ShaderResourceView* TextureManager::getTexture()
{
	return m_texture;
}




