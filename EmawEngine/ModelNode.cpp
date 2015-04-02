#include "stdafx.h"
#include "ModelNode.h"
#include <algorithm>

ModelNode::ModelNode(){
	transform = new Transform();
	initializePosition();
	initializeScale();
	initializeRotation();
}

ModelNode::ModelNode(Model* m){
	transform = new Transform();
	model = m;
	initializePosition();
	initializeScale();
	initializeRotation();
}

ModelNode::~ModelNode(){

}

void ModelNode::update(D3DXMATRIX* otherTransform){

	// Apply transform
	transform->createTransform();
	transform->applyTransformation(otherTransform);
	
	// Update children
	for (int i = 0; i < children.size(); i++){
		children.at(i)->update(transform->getTransformMatrix());
	}

}

void ModelNode::render(){

	gdi->VertexPipeline(&model->getVertexBuffer(), transform->getTransformMatrix());

	//Render children.
	for (int i = 0; i < children.size(); i++){
		children.at(i)->render();
	}
}

void ModelNode::setGraphicsDeviceInterface(GraphicsDeviceInterface* graphicsDeviceInterface){
	gdi = graphicsDeviceInterface;
}

void ModelNode::addChild(SceneGraphNode* child){
	children.push_back(child);
}

// Sets the model's position to x, y, z.
void ModelNode::setPosition(float x, float y, float z){
	*posX = x;
	*posY = y;
	*posZ = z;
	transform->resetTranslateMatrix();
	transform->translate(x, y, z);
}

// Sets the model's rotate to rx, ry, rz.
void ModelNode::setRotation(float rx, float ry, float rz){
	*rotX = rx;
	*rotY = ry;
	*rotZ = rz;
	transform->resetRotationMatrix();
	transform->rotateX(rx);
	transform->rotateY(ry);
	transform->rotateZ(rz);
}

// Sets the model's scale to sx, sy, sz.
void ModelNode::setScale(float sx, float sy, float sz){
	*scaleX = sx;
	*scaleY = sy;
	*scaleZ = sz;
	transform->resetScaleMatrix();
	transform->scale(sx, sy, sz);
}

// Rotates the model by angle in the z direction.
void ModelNode::rotateX(float angle){
	*rotX += angle;
	transform->rotateX(*rotX);
}

// Rotates the model by angle in the y direction.
void ModelNode::rotateY(float angle){
	*rotY += angle;
	transform->rotateY(*rotY);
}

// Rotates the model by angle in the z direction.
void ModelNode::rotateZ(float angle){
	*rotZ += angle;
	transform->rotateZ(angle);
}

// Scales the model by sx, sy, sz;
void ModelNode::scale(float sx, float sy, float sz){
	*scaleX += sx;
	*scaleY += sy;
	*scaleZ += sz;
	transform->scale(sz, sy, sz);
}

// Translates the model by x, y, z.
void ModelNode::translate(float x, float y, float z){
	*posX += x;
	*posY += y;
	*posZ += z;
	transform->translate(x, y, z);
}

void ModelNode::resetTransformMatrix(){
	transform->resetTransformMatrix();
}


// ----------------
// Helper Functions
// ----------------

void ModelNode::initializePosition(){
	posX = new float();
	posY = new float();
	posZ = new float();
	*posX = 0;
	*posY = 0;
	*posZ = 0;
}

void ModelNode::initializeScale(){
	scaleX = new float();
	scaleY = new float();
	scaleZ = new float();
	*scaleX = 1;
	*scaleY = 1;
	*scaleZ = 1;
}

void ModelNode::initializeRotation(){
	rotX = new float();
	rotY = new float();
	rotZ = new float();
	*rotX = 1;
	*rotY = 1;
	*rotZ = 1;
}