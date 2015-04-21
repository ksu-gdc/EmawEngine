#include "stdafx.h"
#include "Camera.h"

Camera::Camera(Vector* pos, Vector* rot)
{
	m_position = pos;
	m_rotation = rot;
}

Camera::~Camera(){}

void Camera::setPosition(float x, float y, float z)
{
	m_position->x = x;
	m_position->y = y;
	m_position->z = z;
	return;
}

void Camera::setRotation(float x, float y, float z)
{
	m_rotation->x = x;
	m_rotation->y = y;
	m_rotation->z = z;
	return;
}

void Camera::AddPitch(float y){
	m_rotation->y -= y;
}

void Camera::AddYaw(float x){
	m_rotation->x -= x;
}

void Camera::setPositionPointers(float* x, float* y, float* z){
	m_position->x = *x;
	m_position->y = *y;
	m_position->z = *z;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return D3DXVECTOR3(m_position->x, m_position->y, m_position->z);
}


D3DXVECTOR3 Camera::GetRotation()
{
	return D3DXVECTOR3(m_rotation->x, m_rotation->y, m_rotation->z);
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
	position.x = m_position->x;
	position.y = m_position->y;
	position.z = m_position->z;

	// Set the yaw (X axis), pitch (Y axis), and roll (Z axis) rotations in radians.
	// I know the yaw should be the Y axis, and the pitch the X axis, but the way player uses them they're switched.
	pitch = m_rotation->y;
	yaw = m_rotation->x;
	roll = m_rotation->z;

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