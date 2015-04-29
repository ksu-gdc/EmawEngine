#include "ClientPacket.h"


ClientPacket::ClientPacket()
{
}

ClientPacket::ClientPacket(char * data) {
	char * loc = data;
	//ignore first unsigned int, it is type
	loc += sizeof(unsigned int);
	memcpy(&m_inputCount, loc, sizeof(unsigned int));
	loc += sizeof(unsigned int);

	char line[MAX_INPUT_SIZE];
	for (int i = 0; i < m_inputCount; i++) {
		memcpy(line, loc, MAX_INPUT_SIZE);
		m_input.push_back(line);
		loc += MAX_INPUT_SIZE;
	}
}


ClientPacket::~ClientPacket()
{
}

void ClientPacket::addInput(std::string input) {
	m_input.push_back(input);
	m_inputCount++;
}

char * ClientPacket::pack() {
	m_size = sizeof(unsigned int) * 2
		+ m_inputCount * MAX_INPUT_SIZE;
	char * data = new char[m_size];
	char * loc = data;

	// add the packet type
	unsigned int type = 2;
	memcpy(loc, &type, sizeof(unsigned int));
	loc += sizeof(unsigned int);

	// add the number of inputs
	unsigned int count = m_inputCount;
	memcpy(loc, &count, sizeof(unsigned int));
	loc += sizeof(unsigned int);

	// copy all of our strings into the array
	const char * temp;
	for (int i = 0; i < m_inputCount; i++) {
		temp = m_input[i].c_str();
		memcpy(loc, temp, MAX_INPUT_SIZE);
		loc += MAX_INPUT_SIZE;
	}

	return data;
}

int ClientPacket::size() {
	return m_size;
}

void ClientPacket::printAll() {
	for (int i = 0; i < m_inputCount; i++) {
		std::cout << m_input[i] << "\n";
	}
}
