#pragma once
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

private:
	Vector* _position;
	Vector* _velocity;
	bool _isAlive;
};

