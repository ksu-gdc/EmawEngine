#pragma once
#include "Asset.h"
#include <fbxsdk.h>
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
	void* createMode(std::vector<VERTEX>);
	std::vector<VERTEX> getVertexBuffer();
	void LoadTexture(ID3D11Device*, string);
	ID3D11ShaderResourceView* GetTexture();

	Vector3* m_InitPos;
	Vector3* m_InitScale;
	Vector3* m_InitRot;
	

private:
	std::vector<VERTEX> vertexBuffer;

	void setInitialTransforms(FbxMesh*);
	void applyInitialTransformations();

	Texture* m_Texture;

};

