#pragma once

class Collidable {
public:
	bool collide(Collidable c);
private:
	float x, y, z;
};