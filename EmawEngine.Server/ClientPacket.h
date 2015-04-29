#pragma once

#include <vector>
#include <string>
#include "NetworkData.h"

#include <iostream>

#define MAX_INPUT_SIZE 10

class ClientPacket
{
public:
	ClientPacket();
	ClientPacket(char * data);
	~ClientPacket();

	void addInput(std::string input);
	char * pack();
	int size();
	void printAll();

private:
	std::vector<std::string> m_input;
	unsigned int m_inputCount;
	int m_size;
};

