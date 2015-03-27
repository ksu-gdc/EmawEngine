#include "stdafx.h"
#include "ModelNode.h"
#include <algorithm>

ModelNode::ModelNode(){
	transform = new Transform();
}

ModelNode::ModelNode(Model* m){
	transform = new Transform();
	model = m;
}

ModelNode::~ModelNode(){

}

void ModelNode::input(){

}

void ModelNode::update(D3DXMATRIX* otherTransform){

	// Apply transform
	transform->applyTransformation(otherTransform);
	transform->createTransform();

	// Update children
	for (int i = 0; i < children.size(); i++){
		children.at(i)->update(transform->getTransformMatrix());
	}

}

void ModelNode::render(std::vector<VERTEX>* verticies){

	std::vector<VERTEX> modelVerticies = model->getVertexBuffer();

	// Transform verticies.
	for (int i = 0; i < modelVerticies.size(); i++){
		verticies->push_back(transform->transformVertex(modelVerticies.at(i)));
	}

	//Render children.
	for (int i = 0; i < children.size(); i++){
		children.at(i)->render(verticies);
	}

}

void ModelNode::addChild(SceneGraphNode* child){

	children.push_back(child);

}

void ModelNode::rotateX(float angle){
	transform->rotateX(angle);
}

void ModelNode::rotateY(float angle){
	transform->rotateY(angle);
}

void ModelNode::rotateZ(float angle){
	transform->rotateZ(angle);
}

void ModelNode::scale(float x, float y, float z){
	transform->scale(x, y, z);
}

void ModelNode::translate(float x, float y, float z){
	transform->translate(x, y, z);
}

void ModelNode::resetTransformMatricies(){
	transform = new Transform();
}