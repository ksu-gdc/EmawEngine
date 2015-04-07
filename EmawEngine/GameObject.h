#pragma once

class GameObject
{
public:
	GameObject();
	~GameObject();

	void update(float gameTime);
	void destroy();
	
	// Getters
	Vector3* getPosition();
	Vector3* getVelocity();
	bool getAlive();

	// Setters
	void setPosition(Vector3* v);
	void setVelocity(Vector3* v);
	void setAlive(bool alive);

	Vector3* _position;
	Vector3* _rotation;
	Vector3* _scale;
	Vector3* _velocity;

	bool m_HasCollision;

private:

	bool _isAlive;
	void initializeVector3(Vector3* vector);
};

