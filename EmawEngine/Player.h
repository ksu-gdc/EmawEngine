#pragma once
#include "GameObject.h"
#include "InputManager.h"
class Player :
	public GameObject
{
public:
	Player(Camera*);
	~Player();
	void updatePlayer(HWND hWnd);
	void passToCamera();

private:
	Camera* fpsCamera;
	float speed;
	POINT curPos;
	InputManager* input;
	float fakeRadius;
	// point where mouse pointer sticks, in client coordinates.
	POINT STICKING_POINT;
};

