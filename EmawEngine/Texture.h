#pragma once


#include <d3d11.h>
#include <D3DX11tex.h>



class Texture
{
public:
	Texture();
	//Texture(const Texture&);
	~Texture();
	bool initialize(ID3D11Device*, WCHAR*);
	void unload();
	ID3D11ShaderResourceView* getTexture();

private:
	ID3D11ShaderResourceView* m_texture;
};

