#pragma once

#include <d3d11.h>
#include <D3DX11tex.h>

class Texture : public Asset
{
public:
	Texture(ID3D11Device* device);
	//Texture(const Texture&);
	~Texture();
	bool initialize(ID3D11Device*, WCHAR*);
	ID3D11ShaderResourceView* getTexture();

	void* load(std::string);
	bool unload();

private:
	ID3D11ShaderResourceView* m_texture;
	ID3D11Device* m_device;
};

