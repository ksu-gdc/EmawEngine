#include "stdafx.h"
#include "VoxelChunkNode.h"


VoxelChunkNode::VoxelChunkNode()
{
	point.W = 0.5f;
	point.X = 0.0f;
	point.Y = 0.0f;
	point.Z = 1.0f;
	point.Color = { 1.0f, 0.0f, 0.0f, 0.0f };
	transform = new Transform();
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

	gdi->VoxelPipeline(&point, 1, transform->getTransformMatrix());

	//Render children.
	for (int i = 0; i < children.size(); i++){
		children.at(i)->render();
	}
}
