#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	_position = new Vector();
	_velocity = new Vector();
	_orientation = new Vector();
	_hasCollision = false;
	_isFalling = false;
	_isAlive = true;

	GRAVITY = (-9.81 / 100000.0);
}


GameObject::~GameObject()
{
}

// Logic for updating a game object
void GameObject::update(float gameTime) {
	// Movement

	if (_hasCollision){
		_velocity->x = 0;
		_velocity->y = 0;
		_velocity->z = 0;
	}

	_position->x += _velocity->x;
	_position->y += (_velocity->y + GRAVITY * _isFalling);
	_position->z += _velocity->z;
}

// Logic for destroying a game object
void GameObject::destroy() {

}

// Gets the objects position
Vector* GameObject::getPosition() {
	return _position;
}

// Gets the objects velocity
Vector* GameObject::getVelocity() {
	return _velocity;
}

// Gets whether or not the state of this object is alive
bool GameObject::getAlive() {
	return _isAlive;
}

// Sets the position of the object
void GameObject::setPosition(Vector* v) {
	std::memcpy(_position, v, sizeof(Vector));
}

// Sets the velocity of the object
void GameObject::setVelocity(Vector* v) {
	std::memcpy(_velocity, v, sizeof(Vector));
}

// Sets the isAlive state of the object
void GameObject::setAlive(bool alive) {
	_isAlive = alive;
}

void GameObject::setCollision(bool collision){
	_hasCollision = collision;
}
