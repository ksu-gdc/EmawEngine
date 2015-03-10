//Class for universal sound
//Author: Ondrej Kuzela
#include "stdafx.h"
#include "Sound.h"

Sound::Sound(string i, FMOD::Sound *s){
	id = i;
	sound = s;
}

Sound::~Sound(){
	FMOD_RESULT result;

	result = sound->release();

	checkProblem(result);
}