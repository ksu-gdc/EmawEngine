#include "stdafx.h"
#include "VoxelChunkNode.h"


VoxelChunkNode::VoxelChunkNode(int inx, int iny)
{
	gridx = inx;
	gridy = iny;
	voxSize = 0.5f;
	memset(ChunkBuffer, 0, sizeof(VERTEX) * 65025);
	transform = new Transform();
	float x = gridx * (2 * voxSize) * 17;
	float z = gridy * (2 * voxSize) * 17;
	float y = 0;
	transform->translate(x, y, z);
	length = 0;
}


VoxelChunkNode::~VoxelChunkNode()
{

}

void VoxelChunkNode::update(D3DXMATRIX* higherTransform)
{
	// Apply transform
	transform->createTransform();
	transform->applyTransformation(higherTransform);

	// Update children
	for (int i = 0; i < children.size(); i++){
		children.at(i)->update(transform->getTransformMatrix());
	}
}

void VoxelChunkNode::setGraphicsDeviceInterface(GraphicsDeviceInterface* graphicsDeviceInterface){
	gdi = graphicsDeviceInterface;
}

void VoxelChunkNode::render(){

	gdi->VoxelPipeline(vertBuffer, ChunkBuffer, length, transform->getTransformMatrix());

	//Render children.
	for (int i = 0; i < children.size(); i++){
		children.at(i)->render();
	}
}

/*
void VoxelChunkNode::loadChunkBuffer(VoxelMap* mapGenerator)
{
	Chunk* hold = mapGenerator->GetChunk(gridx, gridy);
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			int k = hold->height_map[i][j] - 1;
			if (hold->chunk[i][j][k] == 1)
			{
				ChunkBuffer[length].X = (float)i;
				ChunkBuffer[length].Y = (float)k;
				ChunkBuffer[length].Z = (float)j;
				ChunkBuffer[length].W = voxSize;
				if (length % 4 == 0) ChunkBuffer[length].Color = { 0.0f, 0.0f, 0.0f, 0.0f };
				else if (length % 4 == 1) ChunkBuffer[length].Color = { 0.0f, 1.0f, 0.0f, 0.0f };
				else if (length % 4 == 2) ChunkBuffer[length].Color = { 1.0f, 0.0f, 0.0f, 0.0f };
				else if (length % 4 == 3) ChunkBuffer[length].Color = { 0.0f, 0.0f, 1.0f, 0.0f };
				else ChunkBuffer[length].Color = { 1.0f, 1.0f, 1.0f, 0.0f };
				length++;
			}
		}
	}
	vertBuffer = gdi->CreateVertexBuffer(length);
}
*/
//Old chunk loader, unoptimized, runs longer. probably because it creeps upwards slower (why is that happening?)

void VoxelChunkNode::loadChunkBuffer(VoxelMap* mapGenerator)
{

	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			for (int k = 0; k < 225; k++)
			{
				if (mapGenerator->GetChunkValue(gridx, gridy, i, j, k) == 1)
				{
					ChunkBuffer[length].X = (float)i;
					ChunkBuffer[length].Y = (float)k;
					ChunkBuffer[length].Z = (float)j;
					ChunkBuffer[length].W = voxSize;
					float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					ChunkBuffer[length].Color = { r, g, b, 1.0f };
					length++;
				}
			}
		}
	}
	vertBuffer = gdi->CreateVertexBuffer(length);
}