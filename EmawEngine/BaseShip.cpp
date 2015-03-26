#include "stdafx.h"
#include "BaseShip.h"
#include <algorithm>

BaseShip::BaseShip(){
	transform = NULL;
}

BaseShip::BaseShip(std::vector<VERTEX>* verticies){
	transform = NULL;
	float rotate[] = { 0.99999995769, -0.0002908882, 0.0, 0.0002908882, 0.99999995769, 0.0, 0.0, 0.0, 1.0 };
	transform = new Transform(rotate);
	vertexBuffer = *verticies;
}

BaseShip::~BaseShip(){

}

void BaseShip::input(){

}

std::vector<VERTEX>* BaseShip::update(Transform* t){

	Transform* newTransform = NULL;

	std::vector<VERTEX>* totalVerticies = new std::vector<VERTEX>();
	std::vector<VERTEX>* childVerticies = new std::vector<VERTEX>();

	if (transform != NULL){
		newTransform = transform;
	}

	if (t != NULL){
		newTransform = transform->multiply(t);
	}

	// Apply transform
	if (newTransform != NULL){
		for (int i = 0; i < vertexBuffer.size(); i++){
			vertexBuffer[i] = newTransform->transformVertex(vertexBuffer[i]);
		}
	}

	totalVerticies->insert(totalVerticies->end(), vertexBuffer.begin(), vertexBuffer.end());

	// Update children
	for (int i = 0; i < children.size(); i++){
		children.at(i)->update(newTransform);
		totalVerticies->insert(totalVerticies->end(), childVerticies->begin(), childVerticies->end());
	}

	return totalVerticies;

}

void BaseShip::render(){

	/*std::vector<VERTEX> vertices = e->getModel()->getVertexBuffer();
	//vertices = m->getVertexBuffer();

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
	bd.ByteWidth = sizeof(VERTEX) * vertices.size();             // size is the VERTEX struct * 3
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

	m_Device->CreateBuffer(&bd, NULL, &m_VertBuffer);       // create the buffer

	D3D11_MAPPED_SUBRESOURCE ms;
	m_Context->Map(m_VertBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);   // map the buffer
	memcpy(ms.pData, vertices.data(), vertices.size() * sizeof(VERTEX));                // copy the data
	m_Context->Unmap(m_VertBuffer, NULL);*/

	//Render children.
	for (int i = 0; i < children.size(); i++){
		children.at(i)->render();
	}

}

void BaseShip::addChild(GameObjectNode* child){

	children.push_back(child);

}