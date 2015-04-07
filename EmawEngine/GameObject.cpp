#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	_position = new Vector3();
	_rotation = new Vector3();
	_scale = new Vector3();
	_velocity = new Vector3();

	initializeVector3(_position);
	initializeVector3(_rotation);
	initializeVector3(_scale);
	initializeVector3(_velocity);
	_isAlive = true;
}


GameObject::~GameObject()
{
}

// Logic for updating a game object
void GameObject::update(float gameTime) {
	// Movement
	*_position->x += *_velocity->x;
	*_position->y += *_velocity->y;
	*_position->z += *_velocity->z;
}

// Logic for destroying a game object
void GameObject::destroy() {

}

// Gets the objects position
Vector3* GameObject::getPosition() {
	return _position;
}

// Gets the objects velocity
Vector3* GameObject::getVelocity() {
	return _velocity;
}

// Gets whether or not the state of this object is alive
bool GameObject::getAlive() {
	return _isAlive;
}

// Sets the position of the object
void GameObject::setPosition(Vector3* v) {
	std::memcpy(_position, v, sizeof(Vector3));
}

// Sets the velocity of the object
void GameObject::setVelocity(Vector3* v) {
	std::memcpy(_velocity, v, sizeof(Vector3));
}

// Sets the isAlive state of the object
void GameObject::setAlive(bool alive) {
	_isAlive = alive;
}

void GameObject::initializeVector3(Vector3* vector){
	vector->x = new float();
	vector->y = new float();
	vector->z = new float();
}
