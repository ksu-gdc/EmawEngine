// Utilities used in sound library
//Author: Ondrej Kuzela

#pragma once
#include <exception>
#include "fmod/fmod.hpp"

//Maximal possible volume
#define MAX_VOLUME 2.0f

//Minimal volume
#define MIN_VOLUME 0.0f

//Default volume
#define DEFAULT_VOLUME 1.0f

//Number of channels
#define CHANNELS_COUNT 100

//See http://www.fmod.org/docs/content/generated/FMOD_System_Set3DSettings.html
#define DOPPLER_SCALE 1.0
#define ROLLOFF_SCALE 1.0f

//3D distance factor, 1.0f means meter and 3.28f means feet
//How many unit per meter does the engine have
#define DISTANCE_FACTOR 1.0f

//3D channel velocity
extern FMOD_VECTOR TD_VELOCITY;

//3D channel forward vector
//Test constant
extern FMOD_VECTOR FORWARD_ORIENTATION;

//3D channel up vector
//Test constant
extern FMOD_VECTOR UP_ORIENTATION;

//Update time
//Test constant
extern int UPDATE_TIME;

//Sound exception
class fmodexception : public std::exception
{
	virtual const char* what() const throw()
	{
		return "FMOD sound exception!";
	}
};

//Sound exception object
extern fmodexception fmodex;

//Checking the result value of FMOD methods
bool checkResult(FMOD_RESULT result);

//Solving the result value of FMOD methods
void checkProblem(FMOD_RESULT result);