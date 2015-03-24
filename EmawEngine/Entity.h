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
	Vector position;
	Vector orientation;
	DirectX::XMMATRIX* getMatrix();
	void update();
private:
	Model* model;
	DirectX::XMMATRIX* worldMatrix;
	void updateMatrix();
};

