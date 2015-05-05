#pragma once
#include "GameObject.h"
#include "InputManager.h"

class Player :
	public GameObject
{
public:
	Player();
	~Player();
	void updatePlayer(HWND hWnd, bool collision);
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

