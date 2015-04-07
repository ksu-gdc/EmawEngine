#pragma once

#include "GameObject.h"
#include "InputManager.h"

class PlayerObject : public GameObject {

public:
	PlayerObject();
	~PlayerObject();
	void update(float);
	void setInputManager(InputManager*);
	void setCamera(Camera*);

private:

	Camera* m_Camera;
	InputManager* m_InputManager;

	void initializeVector3(Vector3*);
		
};