#pragma once

class Entity
{
public:
	Entity();
	~Entity();
	Vector3 orientation;
	Model* getModel();
	Vector3 position;
	DirectX::XMMATRIX* getMatrix();
	void update();
private:
	
	Vector3 scale;
	DirectX::XMMATRIX worldMatrix;
	void updateMatrix();
protected:
	Model* model;
};

