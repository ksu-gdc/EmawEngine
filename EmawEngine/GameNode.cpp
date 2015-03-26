#include "stdafx.h"
#include "GameNode.h"
#include <algorithm>

GameNode::GameNode(){
	transform = NULL;
}

GameNode::~GameNode(){

}

void GameNode::input(){

}

std::vector<VERTEX>* GameNode::update(Transform* t){

	std::vector<VERTEX>* totalVerticies = new std::vector<VERTEX>();
	std::vector<VERTEX>* parentVerticies = new std::vector<VERTEX>();
	std::vector<VERTEX>* childVerticies = new std::vector<VERTEX>();

	Transform* newTransform = transform;

	if (t != NULL){
		newTransform = transform->multiply(t);
	}

	// Apply transform

	// Update children
	for (int i = 0; i < children.size(); i++){

		childVerticies = children.at(i)->update(newTransform);
		totalVerticies->insert(totalVerticies->end(), childVerticies->begin(), childVerticies->end());
	}

	return totalVerticies;

}

void GameNode::render(){

	//Render children.
	for (int i = 0; i < children.size(); i++){
		children.at(i)->render();
	}

}

void GameNode::addChild(GameObjectNode* child){

	children.push_back(child);

}