#include "stdafx.h"
#include "Entity.h"



Entity::Entity()
{
	model = new Model();
	model->load("models/test2.fbx");
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

DirectX::XMMATRIX* Entity::getMatrix()
{
	return &worldMatrix;
}

void Entity::update()
{
	position.z += 0.0001;
	if (orientation.y < 6.28)
		orientation.y += .001;
	else orientation.y = 0;
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