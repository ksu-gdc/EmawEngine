#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	up = DirectX::XMLoadFloat4(new DirectX::XMFLOAT4(0, 1, 0, 1));

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
	return &DirectX::XMMatrixLookToLH(DirectX::XMLoadFloat4(new DirectX::XMFLOAT4(0, 0, 0, 0)), DirectX::XMQuaternionRotationRollPitchYaw(orientation.x, orientation.y, orientation.z), up);
}

DirectX::XMMATRIX* Camera::getProjTransform() {
	return &DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearPlane, farPlane);
}