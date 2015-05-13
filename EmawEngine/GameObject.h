#pragma once
#include "Entity.h"
#include "MovingCollidable.h"

class GameObject : public MovingCollidable
{
public:
	GameObject();
	~GameObject();

	void update(float gameTime);
	void destroy();
	
	// Getters
	Vector* getPosition();
	Vector* getLastPosition();
	Vector* getVelocity();
	bool getAlive();

	// Setters
	void setPosition(Vector* v);
	void setVelocity(Vector* v);
	void setAlive(bool alive);
	void setCollision(bool collision);

	float getX();
	float getY();
	float getZ();

	float getLastX();
	float getLastY();
	float getLastZ();

	float getRadius();
	float getHeight();
	void pushBack();
	void pushBack(float x, float y, float z);

protected:
	Vector* _position;
	Vector* _lastPosition;
	Vector* _velocity;
	Vector* _orientation;
	bool _hasCollision;
	bool _isFalling;
	bool _isAlive;

	float GRAVITY;
};

