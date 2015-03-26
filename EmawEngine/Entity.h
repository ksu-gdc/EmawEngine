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
	Vector orientation;
	Model* getModel();
	Vector* getPosition();
	DirectX::XMMATRIX* getMatrix();
	void update();
private:
	Model* model;
	Vector position;
	
	Vector scale;
	DirectX::XMMATRIX worldMatrix;
	void updateMatrix();
};

