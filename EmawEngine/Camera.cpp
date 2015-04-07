#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	m_positionX = new float();
	m_positionY = new float();
	m_positionZ = new float();

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}

Camera::~Camera(){}

void Camera::setPosition(float x, float y, float z)
{
	*m_positionX = x;
	*m_positionY = y;
	*m_positionZ = z;
	return;
}

void Camera::setRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

void Camera::AddPitch(float y){
	m_rotationY -= y;
}

void Camera::AddYaw(float x){
	m_rotationX -= x;
}

void Camera::setPositionPointers(float* x, float* y, float* z){
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return D3DXVECTOR3(*m_positionX, *m_positionY, *m_positionZ);
}


D3DXVECTOR3 Camera::GetRotation()
{
	return D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);
}

D3DXMATRIX Camera::GetViewMatrix()
{
	return m_viewMatrix;
}


void Camera::Render(){

	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = *m_positionX;
	position.y = *m_positionY;
	position.z = *m_positionZ;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	m_LookAt.x = 0.0f;
	m_LookAt.y = 0.0f;
	m_LookAt.z = 1.0f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&m_LookAt, &m_LookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	m_LookAt = position + m_LookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &m_LookAt, &up);

	return;

}