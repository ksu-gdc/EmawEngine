#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include "ModelNode.h"
class Player :
	public GameObject
{
public:
	Player(GraphicsDeviceInterface* gdi);
	~Player();
	void updatePlayer(HWND hWnd);
	void passToCamera();
	Camera* getCamera();
	Model* model;
	ModelNode* node;

private:
	Camera* fpsCamera;
	float speed;
	POINT curPos;
	InputManager* input;
	float fakeRadius;
	// point where mouse pointer sticks, in client coordinates.
	POINT STICKING_POINT;
};

