#include "stdafx.h"
#include "Entity.h"


Entity::Entity()
{
	model = new Model();
	model->load("models/cube-above-rot-2.fbx");
	//model->load("models/bell.fbx");

	position = { 0, 0, 0 };
	orientation = DirectX::XMLoadFloat4(new DirectX::XMFLOAT4(0, 0, 0, 0));
	worldMatrix = new DirectX::XMMATRIX(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}


Entity::~Entity()
{
	delete worldMatrix;
}

Model* Entity::getModel() {
	return model;
}

DirectX::XMMATRIX* Entity::getMatrix()
{
	return worldMatrix;
}

void Entity::update()
{
	//position.z += 0.0001;
	updateMatrix();
}

void Entity::updateMatrix()
{
	worldMatrix->r[3] = DirectX::XMVectorSetByIndex(worldMatrix->r[3], position.x, 0);
	worldMatrix->r[3] = DirectX::XMVectorSetByIndex(worldMatrix->r[3], position.y, 1);
	worldMatrix->r[3] = DirectX::XMVectorSetByIndex(worldMatrix->r[3], position.z, 2);
}