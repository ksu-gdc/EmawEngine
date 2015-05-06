#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include "VoxelMap.h"

class Player :
	public GameObject
{
public:
	Player(VoxelMap* worldGenerator);
	~Player();
	void updatePlayer(HWND hWnd);
	void passToCamera();
	Camera* getCamera();

private:
	Camera* fpsCamera;
	float speed;
	POINT curPos;
	InputManager* input;
	float fakeRadius;
	// point where mouse pointer sticks, in client coordinates.
	POINT STICKING_POINT;
};

