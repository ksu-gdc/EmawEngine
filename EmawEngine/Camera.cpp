#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	up = DirectX::XMVectorSet(0, 1, 0, 1);
	orientation = DirectX::XMVectorSet(1, 1, 1, 0);

	fov = DirectX::XM_PIDIV2;
	nearPlane = 0.01;
	farPlane = 100;
	aspect = 1;

	// camera doesn't need a model
	model->~Model();
}


Camera::~Camera()
{
}

DirectX::XMMATRIX* Camera::getViewTransform() {
	return &DirectX::XMMatrixLookToLH(DirectX::XMVectorSet(0, 0, 0, 0), orientation, up);
}

DirectX::XMMATRIX* Camera::getProjTransform() {
	return &DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearPlane, farPlane);
}