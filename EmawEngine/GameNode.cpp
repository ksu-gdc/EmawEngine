#include "stdafx.h"
#include "GameNode.h"
#include <algorithm>

GameNode::GameNode(){
	transform = new Transform();
}

GameNode::~GameNode(){

}

void GameNode::input(){

}

void GameNode::update(D3DXMATRIX* otherTransform){

	// Apply transform
	transform->applyTransformation(otherTransform);
	transform->createTransform();


	// Update children
	for (int i = 0; i < children.size(); i++){
		children.at(i)->update(transform->getTransformMatrix());
	}

}

void GameNode::render(std::vector<VERTEX>* verticies){

	//Render children.
	for (int i = 0; i < children.size(); i++){
		children.at(i)->render(verticies);
	}

}

void GameNode::addChild(SceneGraphNode* child){

	children.push_back(child);

}