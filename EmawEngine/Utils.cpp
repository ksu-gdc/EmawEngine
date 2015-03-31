//Utilities used in sound library
//Author: Ondrej Kuzela

#include "stdafx.h"
#include "Utils.h"
#pragma comment(lib, "fmod/fmod_vc.lib")

//Sound exception object
fmodexception fmodex;

//3D channel velocity
FMOD_VECTOR TD_VELOCITY = { 0.0f, 0.0f, 0.0f };

//3D channel forward vector
//Test constant
FMOD_VECTOR FORWARD_ORIENTATION = { 0.0f, 0.0f, 1.0f };

//3D channel up vector
//Test constant
FMOD_VECTOR UP_ORIENTATION = { 0.0f, 1.0f, 0.0f };

//Update time
//Test constant
int UPDATE_TIME = 50;

//Checking the result value of FMOD methods
bool checkResult(FMOD_RESULT result){
	return (result == FMOD_OK);
}

//Solving the result value of FMOD methods
void checkProblem(FMOD_RESULT result){
	if (!checkResult(result)){
		throw fmodex;
	}
}