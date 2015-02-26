#pragma once
#include "Asset.h"
#include <fbxsdk.h>
#include <vector>

struct Vertex {
	float x;
	float y;
	float z;
};

// a, b, and c are indicies in the vertex buffer
struct Triangle {
	int a;
	int b;
	int c;
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
	std::vector<Triangle> getTriangleList();
private:
	std::vector<Vertex> vertexBuffer;
	std::vector<Triangle> triangleList;
};

