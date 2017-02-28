#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include "VoxelMap.h"
#include "CollisionObject.h"
#include "ModelNode.h"

class Player :
	public GameObject
{
public:
	//VoxelCollision* voxelCollider;
	VoxelMap* map;
	CollisionObject collisionObject;
	Player(GraphicsDeviceInterface*, VoxelMap*);
	~Player();
	bool hasCollision();
	void updatePlayer(HWND, DWORD);
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

