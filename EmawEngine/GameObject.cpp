#include "stdafx.h"
#include "GameObject.h"
#include "CollisionManager.h"


GameObject::GameObject()
{
	_position = new Vector();
	_lastPosition = new Vector();
	_velocity = new Vector();
	_orientation = new Vector();
	_hasCollision = false;
	_isFalling = false;
	_isAlive = true;
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

	std::memcpy(_lastPosition, _position, sizeof(Vector));
	_position->x += _velocity->x;
	_position->y += (_velocity->y);
	_position->z += _velocity->z;
}

// Logic for destroying a game object
void GameObject::destroy() {

}

// Gets the objects position
Vector* GameObject::getPosition() {
	return _position;
}

// Gets the objects last position
Vector* GameObject::getLastPosition() {
	return _lastPosition;
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
	std::memcpy(_lastPosition, _position, sizeof(Vector));
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

float GameObject::getX(){
	return _position->x;
}

float GameObject::getY(){
	return _position->y;
}

float GameObject::getZ(){
	return _position->z;
}

float GameObject::getLastX(){
	return _lastPosition->x;
}

float GameObject::getLastY(){
	return _lastPosition->y;
}

float GameObject::getLastZ(){
	return _lastPosition->z;
}

float GameObject::getRadius(){
	return 0.5f;
}

float GameObject::getHeight(){
	return 1.0f;
}

void GameObject::pushBack(){
	_position->x = _lastPosition->x;
	_position->y = _lastPosition->y;
	_position->z = _lastPosition->z;
}

void GameObject::pushBack(float x, float y, float z){
	_position->x = _lastPosition->x = x;
	_position->y = _lastPosition->y = y;
	_position->z = _lastPosition->z = z;
}