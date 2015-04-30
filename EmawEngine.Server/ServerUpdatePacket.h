#pragma once

#include <vector>
#include <string>
#include "NetworkData.h"

#include <iostream>

#define MAX_INPUT_SIZE 10

class ServerUpdatePacket
{
public:
	ServerUpdatePacket();
	ServerUpdatePacket(char * data);
	~ServerUpdatePacket();

	void addPlayer(Vector3 position, Vector3 orientation, bool firing);
	char * pack();
	int size();
	void printAll();

private:
	std::vector<Vector3> m_pPos;
	std::vector<Vector3> m_pOri;
	std::vector<bool> m_pFire;

	unsigned int m_playerSize;
	unsigned int m_pCount;
	int m_size;
};

