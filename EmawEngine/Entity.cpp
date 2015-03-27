#include "stdafx.h"
#include "Entity.h"


Entity::Entity()
{
	model = new Model();
	model->load("models/cube-small.fbx");
	//model->load("models/bell.fbx");

	position = { 0, 0, 0 };
	orientation = { 0, 0, 0 };

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