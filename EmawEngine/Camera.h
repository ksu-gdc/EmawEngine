#pragma once

#include "stdafx.h"
#include "MovingCollidable.h"

class Camera : public MovingCollidable{

public:
	Camera(Vector*, Vector*);
	~Camera();

	void setPosition(float, float, float);
	void setRotation(float, float, float);
	void setPositionPointers(float* x, float* y, float* z);

	void AddPitch(float);
	void AddYaw(float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	D3DXMATRIX GetViewMatrix();

	void Render();

private:
	Vector* m_position;
	Vector* m_rotation;
	
	D3DXVECTOR3 m_LookAt;

	D3DXMATRIX m_viewMatrix;



};