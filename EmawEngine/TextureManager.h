#pragma once


#include <d3d11.h>
#include <D3DX11tex.h>



class TextureManager
{
public:
	TextureManager();
	TextureManager(const TextureManager&);
	~TextureManager();
	bool initialize(ID3D11Device*, WCHAR*);
	void unload();
	ID3D11ShaderResourceView* getTexture();

private:
	ID3D11ShaderResourceView* m_texture;
};

