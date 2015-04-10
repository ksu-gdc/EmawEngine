#pragma once
#include "SceneGraphNode.h"
#include "VoxelMap.h"
class VoxelChunkNode :
	public SceneGraphNode
{
public:
	VoxelChunkNode(int, int);
	~VoxelChunkNode();
	void update(D3DXMATRIX*);
	void render();
	void setGraphicsDeviceInterface(GraphicsDeviceInterface*);
	void loadChunkBuffer(VoxelMap*);

private:
	int gridx, gridy;
	float posX, posY, posZ;
	float rotX, rotY, rotZ;
	float scaleX, scaleY, scaleZ;
	int length;
	VERTEX ChunkBuffer[65025];
	ID3D11Buffer* vertBuffer;
	float voxSize;
};

