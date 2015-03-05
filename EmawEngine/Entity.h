#pragma once

struct Vector {
	float x;
	float y;
	float z;
};

class Entity
{
public:
	Entity();
	~Entity();
	Model* getModel();
	Vector* getPosition();
private:
	Model* model;
	Vector position;
	Vector orientation;
};

