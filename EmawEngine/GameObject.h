#pragma once
#include "Entity.h"
class GameObject
{
public:
	GameObject();
	~GameObject();

	void update(float gameTime);
	void destroy();
	
	// Getters
	Vector* getPosition();
	Vector* getVelocity();
	bool getAlive();

	// Setters
	void setPosition(Vector* v);
	void setVelocity(Vector* v);
	void setAlive(bool alive);
	void setCollision(bool collision);

protected:
	Vector* _position;
	Vector* _velocity;
	Vector* _orientation;
	bool _hasCollision;
	bool _isFalling;
	bool _isAlive;

	float GRAVITY;
};

