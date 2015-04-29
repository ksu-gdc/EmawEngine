#include "ClientPacket.h"


ClientPacket::ClientPacket()
{
}


ClientPacket::~ClientPacket()
{
}

void ClientPacket::addInput(std::string input) {
	m_input.push_back(input);
	m_inputCount++;
}

char * ClientPacket::pack() {
	char * data = new char[sizeof(unsigned int) + m_inputCount * MAX_INPUT_SIZE];
	char * loc = data;

	// add the packet type
	unsigned int type = 2;
	memcpy(loc, &type, sizeof(unsigned int));

	// copy all of our strings into the array
	char * temp;
	for (int i = 0; i < m_inputCount; i++) {
		temp = m_input[i].c_str;
		memcpy(loc, temp, MAX_INPUT_SIZE);
		loc += MAX_INPUT_SIZE;
	}
}
