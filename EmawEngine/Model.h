#pragma once
#include "Asset.h"
#include "Entity.h"
#include "texture.h"

class Model : public Asset
{
public:
	Model();
	Model(std::vector<VERTEX>);
	~Model();
	void* load(std::string);
	void* getData();
	bool unload();
	std::vector<VERTEX> getVertexBuffer();
	void LoadTexture(ID3D11Device*, string);
	ID3D11ShaderResourceView* GetTexture();
	

private:
	std::vector<VERTEX> vertexBuffer;

	Texture* m_Texture;

};

