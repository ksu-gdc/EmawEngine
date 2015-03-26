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
	DirectX::XMVECTOR orientation;
	DirectX::XMMATRIX* getMatrix();
	void update();
private:
	DirectX::XMMATRIX* worldMatrix;
	void updateMatrix();
protected:
	Model* model;
};

