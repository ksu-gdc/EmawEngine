#pragma once
#include "Asset.h"
#include <fbxsdk.h>
#include <vector>

struct Vertex {
	float x;
	float y;
	float z;
};

class Model :
	public Asset
{
public:
	Model();
	~Model();
	void* load(char*);
	void* getData();
	bool unload();
	std::vector<Vertex> getVertexBuffer();
private:
	std::vector<Vertex> vertexBuffer;
};

