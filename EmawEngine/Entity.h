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
	DirectX::XMMATRIX* getMatrix();
	void update();
private:
	Model* model;
	Vector position;
	Vector orientation;
	DirectX::XMMATRIX* worldMatrix;
	void updateMatrix();
};

