#pragma once

#include <vector>
#include <string>
#include "NetworkData.h"

#define MAX_INPUT_SIZE 10

class ClientPacket
{
public:
	ClientPacket();
	~ClientPacket();

	void addInput(std::string input);

	char * pack();

private:
	std::vector<std::string> m_input;
	unsigned int m_inputCount;
};

