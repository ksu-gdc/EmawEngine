#include "stdafx.h"
#include "ModelNode.h"
#include <algorithm>

ModelNode::ModelNode(){
	m_Transform = new Transform();
	initializePosition();
	initializeScale();
	initializeRotation();
}

ModelNode::ModelNode(Model* m){
	m_Transform = new Transform();
	m_Model = m;
	initializePosition();
	initializeScale();
	initializeRotation();
	ModelNode::setPosition(*m_Model->m_InitPos->x, *m_Model->m_InitPos->y, *m_Model->m_InitPos->z);
	ModelNode::setRotation(*m_Model->m_InitRot->x, *m_Model->m_InitRot->y, *m_Model->m_InitRot->z);
	ModelNode::setScale(*m_Model->m_InitScale->x, *m_Model->m_InitScale->y, *m_Model->m_InitScale->z);
}

ModelNode::~ModelNode(){

}

void ModelNode::update(D3DXMATRIX* otherTransform){

	// Apply transform
	m_Transform->createTransform();
	m_Transform->applyTransformation(otherTransform);
	
	// Update children
	for (int i = 0; i < children.size(); i++){
		children.at(i)->update(m_Transform->getTransformMatrix());
	}

}

void ModelNode::render(){

	gdi->VertexPipeline(m_VertBuffer, &m_Model->getVertexBuffer(), m_Transform->getTransformMatrix());

	//Render children.
	for (int i = 0; i < children.size(); i++){
		children.at(i)->render();
	}
}

void ModelNode::setGraphicsDeviceInterface(GraphicsDeviceInterface* graphicsDeviceInterface){
	gdi = graphicsDeviceInterface;
	initializeVertexBuffer();
}

void ModelNode::initializeVertexBuffer(){
	m_VertBuffer = gdi->CreateVertexBuffer(m_Model->getVertexBuffer().size());
}

void ModelNode::addChild(SceneGraphNode* child){
	children.push_back(child);
}

// Sets the model's position to x, y, z.
void ModelNode::setPosition(float x, float y, float z){
	*posX = x;
	*posY = y;
	*posZ = z;
	m_Transform->resetTranslateMatrix();
	m_Transform->translate(x, y, z);
}

// Sets the model's rotate to rx, ry, rz.
void ModelNode::setRotation(float rx, float ry, float rz){
	*rotX = rx;
	*rotY = ry;
	*rotZ = rz;
	m_Transform->resetRotationMatrix();
	m_Transform->rotateX(rx);
	m_Transform->rotateY(ry);
	m_Transform->rotateZ(rz);
}

// Sets the model's scale to sx, sy, sz.
void ModelNode::setScale(float sx, float sy, float sz){
	*scaleX = sx;
	*scaleY = sy;
	*scaleZ = sz;
	m_Transform->resetScaleMatrix();
	m_Transform->scale(sx, sy, sz);
}

// Rotates the model by angle in the z direction.
void ModelNode::rotateX(float angle){
	*rotX += angle;
	m_Transform->rotateX(*rotX);
}

// Rotates the model by angle in the y direction.
void ModelNode::rotateY(float angle){
	*rotY += angle;
	m_Transform->rotateY(*rotY);
}

// Rotates the model by angle in the z direction.
void ModelNode::rotateZ(float angle){
	*rotZ += angle;
	m_Transform->rotateZ(angle);
}

// Scales the model by sx, sy, sz;
void ModelNode::scale(float sx, float sy, float sz){
	*scaleX += sx;
	*scaleY += sy;
	*scaleZ += sz;
	m_Transform->scale(sz, sy, sz);
}

// Translates the model by x, y, z.
void ModelNode::translate(float x, float y, float z){
	*posX += x;
	*posY += y;
	*posZ += z;
	m_Transform->translate(x, y, z);
}

void ModelNode::resetTransformMatrix(){
	m_Transform->resetTransformMatrix();
}

// ----------------
// Helper Functions
// ----------------

void ModelNode::initializePosition(){
	posX = new float();
	posY = new float();
	posZ = new float();
}

void ModelNode::initializeScale(){
	scaleX = new float();
	scaleY = new float();
	scaleZ = new float();
}

void ModelNode::initializeRotation(){
	rotX = new float();
	rotY = new float();
	rotZ = new float();
}