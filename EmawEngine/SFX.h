//Class for 3D SFX
//Author: Ondrej Kuzela
#pragma once
#include "Sound.h"
#pragma once


class SFX : public Sound{
public:
	SFX(string name, FMOD::Sound *s) :Sound(name, s){

	}
};