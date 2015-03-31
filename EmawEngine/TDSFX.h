//Class for 3D SFX
//Author: Ondrej Kuzela
#pragma once
#include "SFX.h"
#include "Position.h"


class TDSFX : public SFX{
private:
	Position* position;
public:
	TDSFX(string name, FMOD::Sound *s, Position* p);
	~TDSFX();
	Position* getPosition();
};