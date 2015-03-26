#pragma once
#include "Entity.h"
class Camera :
	public Entity
{
public:
	Camera();
	~Camera();
	DirectX::XMMATRIX* getViewTransform();
	DirectX::XMMATRIX* getProjTransform();
private:
	DirectX::XMVECTOR up;
	float fov;
	float nearPlane;
	float farPlane;
	float aspect;
};

