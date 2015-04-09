//Static
//Author: Ondrej Kuzela

#pragma once
#include <string>
#include <list>
#include "Collidable.h"

using namespace std;

class StaticCollider {
public:
	virtual bool checkCollisions(list<Collidable> collidables);
	virtual bool checkCollisions(Collidable c);
};