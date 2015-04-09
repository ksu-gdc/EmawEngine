#pragma once
#include "Asset.h"
#include <fbxsdk.h>
#include <vector>

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
	void GetFbxInfo(FbxNode* Node);
private:
	std::vector<VERTEX> vertexBuffer;
};

