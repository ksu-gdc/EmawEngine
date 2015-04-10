#pragma once
#include "SceneGraphNode.h"
class VoxelChunkNode :
	public SceneGraphNode
{
public:
	VoxelChunkNode();
	~VoxelChunkNode();
	void update(D3DXMATRIX*);
	void render();
	void setGraphicsDeviceInterface(GraphicsDeviceInterface*);

private:
	float posX, posY, posZ;
	float rotX, rotY, rotZ;
	float scaleX, scaleY, scaleZ;
	VERTEX point;
	float voxSize;
};

