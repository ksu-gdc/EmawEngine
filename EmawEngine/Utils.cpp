//Utilities used in sound library
//Author: Ondrej Kuzela

#include "stdafx.h"
#include "Utils.h"
#pragma comment(lib, "fmod/fmod_vc.lib")

//Sound exception object
fmodexception fmodex;

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