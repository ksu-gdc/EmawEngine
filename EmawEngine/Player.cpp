#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"

Player::Player(Camera * camera)
{
	input = InputManager::getInstance();
	fpsCamera = camera;
	speed = 0.01;
	lastPos = input->getMouseScreenPos();
	fakeRadius = 100;
	_position->x = 0;
	_position->y = 0;
	_position->z = -10;
	_orientation->x = 0;
	_orientation->y = 0;
	_orientation->z = 0;
	
}


Player::~Player()
{
}

void Player::updatePlayer()
{
	float zvel = 0;
	float xvel = 0;
	float yvel = 0;
	if (input->keyDown(Key::W))
	{
		zvel += speed;
	}
	if (input->keyDown(Key::S))
	{
		zvel -= speed;
	}
	if (input->keyDown(Key::A))
	{
		xvel -= speed;
	}
	if (input->keyDown(Key::D))
	{
		xvel += speed;
	}
	if (input->keyDown(Key::Space))
	{
		yvel += speed;
	}
	if (input->keyDown(Key::Ctrl))
	{
		yvel -= speed;
	}

	//get change in mouse position from last update.
	curPos = input->getMouseScreenPos();
	long deltax = -(curPos.x - lastPos.x);
	long deltay = curPos.y - lastPos.y;

	lastPos = curPos;
	
	//map the mouse delta to an orientation angle.
	_orientation->x += (float) (deltax / fakeRadius);
	if (_orientation->x > (2 * M_PI)) _orientation->x -= (2 * M_PI);
	else if (_orientation->x < 0) _orientation->x = (2 * M_PI) - _orientation->x;
	
	_orientation->y += (float)(deltay / fakeRadius);
	if (_orientation->y >(2 * M_PI)) _orientation->y -= (2 * M_PI);
	else if (_orientation->y < 0) _orientation->y = (2 * M_PI) - _orientation->y;

	//transform the velocity of the player so that "forward" is always where the player is pointing.
	DirectX::XMMATRIX rotMatrix = DirectX::XMMatrixRotationRollPitchYaw(_orientation->y, _orientation->x, _orientation->z);
	DirectX::XMVECTOR velocity = DirectX::XMVectorSet(xvel, yvel, zvel, 1.0f);
	velocity = DirectX::XMVector3Transform(velocity, rotMatrix);

	_velocity->x = DirectX::XMVectorGetByIndex(velocity, 0);
	_velocity->y = DirectX::XMVectorGetByIndex(velocity, 1);
	_velocity->z = DirectX::XMVectorGetByIndex(velocity, 2);

	update(0);
	passToCamera();
}

void Player::passToCamera()
{
	fpsCamera->setPosition(_position->x, _position->y, _position->z);
	fpsCamera->setRotation(_orientation->y, _orientation->x, _orientation->z);
}
