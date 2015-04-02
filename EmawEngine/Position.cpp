//Class for Position
//Author: Ondrej Kuzela
#include "stdafx.h"
#include "Position.h"

Position::Position(){
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Position::Position(Position* p){
	x = p->getX();
	y = p->getY();
	z = p->getZ();
}

Position::Position(float tX, float tY, float tZ){
	x = tX;
	y = tY;
	z = tZ;
}

void Position::setX(float nX){
	x = nX;
}

void Position::setY(float nY){
	y = nY;
}

void Position::setZ(float nZ){
	z = nZ;
}

float Position::getX(){
	return x;
}

float Position::getY(){
	return y;
}

float Position::getZ(){
	return z;
}

FMOD_VECTOR Position::getVector(){
	FMOD_VECTOR vector = { x, y, z };
	return vector;
}

bool Position::isEmpty(){
	return x == 0.0f && y == 0.0f && z == 0.0f;
}