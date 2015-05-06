#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "VoxelCollision.h"

Player::Player(VoxelMap* worldGenerator)
{
	input = InputManager::getInstance();

	speed = 0.5;
	fakeRadius = 100;

	_position->x = 0;
	_position->y = 0;
	_position->z = 3;
	_orientation->x = M_PI;
	_orientation->y = 0;
	_orientation->z = 0;
	fpsCamera = new Camera(_position, _orientation);
	map = worldGenerator;//TEMP

	// these must match the values in MouseState.cpp
	// todo: make both of these reference the same constant
	STICKING_POINT.x = 300;
	STICKING_POINT.y = 300;
}


Player::~Player()
{
}

bool Player::hasCollision()
{
	D3DXVECTOR3 pos = getCamera()->GetPosition();
	Chunk* chunk = map->GetChunk(pos.x / CHUNK_SIZE, pos.z / CHUNK_SIZE);
	//if (chunk->chunk[pos.x%CHUNK_SIZE][pos.y%CHUNK_HEIGHT][pos.z%CHUNK_SIZE] != 0)
	Vector* point = new Vector;
	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			point->x = i + pos.x;
			point->y = chunk->height_map[i][j];
			point->z = j + pos.z;
			if (collisionObject.hasCollision(CollisionObject(point, 1, 1, 1), 0)) return true;
		}
	}
	return false;
}

void Player::updatePlayer(HWND hWnd)
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
	if (input->keyDown(Key::Ctrl) && !hasCollision())
	{
		yvel -= speed;
	}

	//get change in mouse position from last update.
	curPos = input->getMousePos();
	
	long deltax = curPos.x - STICKING_POINT.x;
	long deltay = curPos.y - STICKING_POINT.y;

	if (deltax != 0 || deltay != 0) {
		// move mouse back to sticking point
		POINT stickingPointScreen = STICKING_POINT;
		ClientToScreen(hWnd, &stickingPointScreen);
		if (!SetCursorPos(stickingPointScreen.x, stickingPointScreen.y)) {
			OutputDebugString(L"failed to set cursor position.\n");
		}
	}
	
	//map the mouse delta to an orientation angle.
	_orientation->x += (float)(deltax / fakeRadius);
	if (_orientation->x > (2 * M_PI)) {
		_orientation->x -= (2 * M_PI);
	}
	else if (_orientation->x < 0) {
		_orientation->x += (2 * M_PI);
	}

	_orientation->y += (float)(deltay / fakeRadius);
	if (_orientation->y > (2 * M_PI)) {
		_orientation->y -= (2 * M_PI);
	}
	else if (_orientation->y < 0) {
		_orientation->y += (2 * M_PI);
	}
	if (_orientation->y < (3 * M_PI / 2) && _orientation->y > M_PI) {
		_orientation->y = (3 * M_PI / 2);
	}
	else if (_orientation->y >(M_PI / 2) && _orientation->y < M_PI) {
		_orientation->y = (M_PI / 2);
	}

	//transform the velocity of the player so that "forward" is always where the player is pointing.
	DirectX::XMMATRIX rotMatrix = DirectX::XMMatrixRotationRollPitchYaw(_orientation->y, _orientation->x, _orientation->z);
	DirectX::XMVECTOR velocity = DirectX::XMVectorSet(xvel, 0, zvel, 1.0f);
	velocity = DirectX::XMVector3Transform(velocity, rotMatrix);

	_velocity->x = DirectX::XMVectorGetByIndex(velocity, 0);
	// yvel is added here because jumping should move you straight up no matter what.
	_velocity->y = DirectX::XMVectorGetByIndex(velocity, 1) +yvel;
	_velocity->z = DirectX::XMVectorGetByIndex(velocity, 2);
	

	update(0);
	passToCamera();
}

Camera* Player::getCamera()
{
	return fpsCamera;
}

void Player::passToCamera()
{
	//fpsCamera->setPosition(_position->x, _position->y, _position->z);
	//fpsCamera->setRotation(_orientation->y, _orientation->x, _orientation->z);
}
