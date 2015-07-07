#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "VoxelCollision.h"

Player::Player(GraphicsDeviceInterface* gdi, VoxelMap* worldGenerator)
{
	input = InputManager::getInstance();

	speed = 0.01;
	fakeRadius = 100;

	_position->x = 20;
	_position->y = 39;
	_position->z = 8;
	std::memcpy(_lastPosition, _position, sizeof(Vector));

	_orientation->x = M_PI;
	_orientation->y = 0;
	_orientation->z = 0;
	fpsCamera = new Camera(_position, _orientation);
	map = worldGenerator;//TEMP

	model = new Model();
	model->load("models/obj-models/cat.obj");
	model->LoadTexture(gdi->m_Device, "textures/cat-flipped.png");

	node = new ModelNode(model);
	node->setGraphicsDeviceInterface(gdi);

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
			point->x = i + float((int(pos.x)/CHUNK_SIZE))*CHUNK_SIZE;
			point->y = chunk->height_map[i][j];
			point->z = j + float((int(pos.z)/CHUNK_SIZE))*CHUNK_SIZE;
			if ((pos.x - point->x) < 1 && (pos.x - point->x) > -1) {
				if ((pos.y - point->y) < 2 && (pos.y - point->y) > -1) {
					if ((pos.z - point->z) < 1 && (pos.z - point->z) > -1) return true;
				}
			}
		}
	}
	return false;
}

void Player::updatePlayer(HWND hWnd)
{
	float zvel = 0;
	float xvel = 0;
	float yvel = 0;
	bool test = hasCollision();
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
		yvel += 2*speed;
	}
	if (input->keyDown(Key::Ctrl) && !test)
	{
		yvel -= speed;
	}
	if (!test)
	{
		yvel -= speed;
	}
	else
	{
		yvel += speed;
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
	_velocity->y = yvel;
	_velocity->z = DirectX::XMVectorGetByIndex(velocity, 2);

	// update scene graph node
	float side_gun_offset = 0.5;
	printf("%f\n", _orientation->x);
	node->setPosition(_position->x + side_gun_offset*cos(_orientation->x), _position->y - 0.9, _position->z - side_gun_offset*sin(_orientation->x));
	node->setRotation(_orientation->y, _orientation->x, _orientation->z);

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
