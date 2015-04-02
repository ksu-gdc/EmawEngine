//Class for universal sound
//Author: Ondrej Kuzela

#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include "fmod/fmod.hpp"
#include "Utils.h"

using namespace std;

class Sound {
public:
	//Sound's id
	string id;

	//FMOD Sound class
	FMOD::Sound *sound;
	Sound(string i, FMOD::Sound *s);
	virtual ~Sound();
};