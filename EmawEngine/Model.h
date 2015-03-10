#pragma once
#include "Asset.h"
#include <fbxsdk.h>
#include <vector>

class Model :
	public Asset
{
public:
	Model();
	Model(std::vector<VERTEX>);
	~Model();
	void* load(char*);
	void* getData();
	bool unload();
	void* createMode(std::vector<VERTEX>);
	std::vector<VERTEX> getVertexBuffer();
private:
	std::vector<VERTEX> vertexBuffer;
};

