//Class for 3D SFX
//Author: Ondrej Kuzela
#include "stdafx.h"
#include "TDSFX.h"

TDSFX::TDSFX(string name, FMOD::Sound *s, Position* p):SFX(name, s){
	position = new Position(p);
}

TDSFX::~TDSFX(){
	delete position;
}

Position* TDSFX::getPosition(){
	return position;
}