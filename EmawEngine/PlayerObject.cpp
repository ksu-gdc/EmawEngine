#include "stdafx.h"
#include "PlayerObject.h"

PlayerObject::PlayerObject(){

	_position = new Vector3();
	_rotation = new Vector3();
	_scale = new Vector3();
	_velocity = new Vector3();

	initializeVector3(_position);
	initializeVector3(_rotation);
	initializeVector3(_scale);
	initializeVector3(_velocity);

	m_HasCollision = false;

	*_position->z = -10;
	*_position->y = 5;
	*_velocity->y = -9.81/100000;
	//*_velocity->y = 0;
}

void PlayerObject::setInputManager(InputManager* ms){
	m_InputManager = ms;
}

void PlayerObject::setCamera(Camera* c){
	m_Camera = c;
}

void PlayerObject::update(float gameTime){

	if (!m_HasCollision){
		if (m_InputManager->keyDown(Z)){
			*_velocity->z = -0.005;
		}
		else{
			*_velocity->z = 0.0;
		}
		if (m_InputManager->keyDown(S)){
			*_velocity->z = 0.005;
		}
		else{
			*_velocity->z = 0.0;
		}
		if (m_InputManager->keyDown(A)){
			*_velocity->x = 0.005;
		}
		else{
			*_velocity->x = 0.0;
		}
		if (m_InputManager->keyDown(D)){
			*_velocity->x = -0.005;
		}
		else{
			*_velocity->x = 0.0;
		}

		m_Camera->AddPitch(m_InputManager->getMousePosDiffX() * .025);
		m_Camera->AddYaw(m_InputManager->getMousePosDiffY() * .025);

		*_position->x += *_velocity->x;
		*_position->y += *_velocity->y;
		*_position->z += *_velocity->z;
	}

	m_HasCollision = false;

};

void PlayerObject::initializeVector3(Vector3* vector){
	vector->x = new float();
	vector->y = new float();
	vector->z = new float();
}