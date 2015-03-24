/*
* The Texture class encapsulates the loading, unloading, and accessing
* of a single texture resource.  For each texture needed an object of this class
* must be instantiated.
*/

#include "stdafx.h"
#include "Texture.h"
#include <d3d11.h>
#include <D3DX11tex.h>


using namespace std;


Texture::Texture(ID3D11Device* device)
{
	m_texture = 0;
	m_device = device;
}

/*
Texture::Texture(const Texture& other)
{

}
*/

Texture::~Texture()
{

}


/*
* initialize takes in a Direct3D Device and a file name of the texture and then
* loads the texture file into the shader resource variable m_textures.
* The texture can now be used to render with.  

* The format of the textures we will be using are .dds files. 
* This is the Direct Draw Surface format that DirectX uses. 
* The tool used to produce .dds files comes with the DirectX SDK. 
* It is under DirectX Utilities and is called DirectX Texture Tool. 
* You can create a new texture of any size and format and then cut and 
* paste your image or other format texture onto it and save it as a .dds file. 
*
* @param device		The Direct3D device
* @param filename	The name of the file we are loading (and location if its not in the same folder as the exe)
*
* @return true if the file loaded, false otherwise
*/
void* Texture::load(std::string str)
{
	HRESULT result; 
	std::wstring stemp = std::wstring(str.begin(), str.end());
	LPCWSTR filename = (LPCWSTR)&stemp[0];
	//Load texture
	result = D3DX11CreateShaderResourceViewFromFile(m_device, filename, NULL, NULL, &m_texture, NULL);
	// Removed to return void
	//if (FAILED(result))
	//	return false;
	//return true;
	return NULL;
}


/*
* The unload function releases the texture resource if it has been loaded and then 
* sets the pointer to null (0)
*/
bool Texture::unload()
{
	//Release the texture resource
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
	return true;
}


/*
* Function called by other objects that need access to the texture shader resource
* so that they can use the texture for rendering.
*/
ID3D11ShaderResourceView* Texture::getTexture()
{
	return m_texture;
}




