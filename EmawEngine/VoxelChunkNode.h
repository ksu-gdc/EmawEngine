#pragma once
#include "SceneGraphNode.h"
#include "VoxelMap.h"
class VoxelChunkNode :
	public SceneGraphNode
{
public:
	VoxelChunkNode();
	~VoxelChunkNode();
	void update(D3DXMATRIX*);
	void render();
	void setGraphicsDeviceInterface(GraphicsDeviceInterface*);
	void loadChunkBuffer(VoxelMap*, int, int);

private:
	float posX, posY, posZ;
	float rotX, rotY, rotZ;
	float scaleX, scaleY, scaleZ;
	int length;
	VERTEX ChunkBuffer[65025];
	ID3D11Buffer* vertBuffer;
	float voxSize;
};

