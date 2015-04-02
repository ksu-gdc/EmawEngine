#pragma once

#include "stdafx.h"

class Camera {

public:
	Camera();
	~Camera();

	void setPosition(float, float, float);
	void setRotation(float, float, float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	D3DXMATRIX GetViewMatrix();

	void Render();

private:
	float m_positionX;
	float m_positionY;
	float m_positionZ;
	float m_rotationX;
	float m_rotationY;
	float m_rotationZ;

	D3DXMATRIX m_viewMatrix;



};