#include "stdafx.h"
#include "gdiPrimerNode.h"


gdiPrimerNode::gdiPrimerNode()
{
	transform = new Transform();
}


gdiPrimerNode::~gdiPrimerNode()
{
}

void gdiPrimerNode::update(D3DXMATRIX* otherTransform){

	// Apply transform
	transform->applyTransformation(otherTransform);
	transform->createTransform();

	// Update children
	for (int i = 0; i < children.size(); i++){
		children.at(i)->update(transform->getTransformMatrix());
	}

}

void gdiPrimerNode::render(){

	//Render children.
	gdi->setShaders((ShaderStruct *)shader->getData());
	for (int i = 0; i < children.size(); i++){
		children.at(i)->render();
	}

}

void gdiPrimerNode::addChild(SceneGraphNode* child){

	children.push_back(child);

}

void gdiPrimerNode::setGraphicsDeviceInterface(GraphicsDeviceInterface* graphicsDeviceInterface){

	gdi = graphicsDeviceInterface;
}


void gdiPrimerNode::setShader(ShaderAsset* shdr)
{
	shader = shdr;
}