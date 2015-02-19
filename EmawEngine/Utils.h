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