#include "stdafx.h"
#include "Entity.h"



Entity::Entity()
{
	model = new Model();
	model->load("models/cube-above-rot-2.fbx");
	//model->load("models/bell.fbx");

	position = { 0, 0, 0 };
	orientation = { 0, 0, 0 };
	scale = { 1, 1, 1 };
	worldMatrix = DirectX::XMMATRIX(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}


Entity::~Entity()
{
}

Model* Entity::getModel() {
	return model;
}

Vector* Entity::getPosition() {
	return &position;
}

DirectX::XMMATRIX* Entity::getMatrix()
{
	return &worldMatrix;
}

void Entity::update()
{
	updateMatrix();
}

void Entity::updateMatrix()
{
	DirectX::XMVECTOR quaternion = DirectX::XMQuaternionRotationRollPitchYaw(orientation.x, orientation.y, orientation.z);
	worldMatrix = DirectX::XMMatrixAffineTransformation(
		DirectX::XMVectorSet(scale.x, scale.y, scale.z, 1),
		DirectX::XMVectorSet(0, 0, 0, 0),
		quaternion,
		DirectX::XMVectorSet(position.x, position.y, position.z, 1)
		);
}