//Class for a source of sound
//Author: Ondrej Kuzela

#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include "fmod/fmod.hpp"
#include "TDSFX.h"

using namespace std;

class SoundSource {
protected:
	TDSFX * sound;
	FMOD::Channel *channel;
	Position* position;
public:
	SoundSource(string name, string filename, Position* position);
	~SoundSource();
	void playSound();
};