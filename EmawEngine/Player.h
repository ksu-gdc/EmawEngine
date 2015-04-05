#pragma once
#include "GameObject.h"
#include "InputManager.h"
class Player :
	public GameObject
{
public:
	Player(Camera*);
	~Player();
	void updatePlayer();
	void passToCamera();

private:
	Camera* fpsCamera;
	float speed;
	POINT lastPos;
	POINT curPos;
	InputManager* input;
	float fakeRadius;
};

