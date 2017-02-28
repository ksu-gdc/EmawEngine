// James Tyson
#include "ClientUpdatePacket.h"
#include "stdafx.h"

// Default constructor
ClientUpdatePacket::ClientUpdatePacket()
{
	m_inputCount = 0;
}

// Constructor that depacks packet data.
ClientUpdatePacket::ClientUpdatePacket(char * data) {
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

// Default destructor.
ClientUpdatePacket::~ClientUpdatePacket()
{
}

// Adds a player input into the packet.
void ClientUpdatePacket::addInput(std::string input) {
	m_input.push_back(input);
	m_inputCount++;
}

// Packs the packet data and returns a char*.
char * ClientUpdatePacket::pack() {
	m_size = sizeof(unsigned int) * 2
		+ m_inputCount * MAX_INPUT_SIZE;
	char * data = new char[m_size];
	char * loc = data;

	// add the packet type
	unsigned int type = CLIENT_UPDATE;
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

// Returns the size of the packet.
int ClientUpdatePacket::size() {
	return m_size;
}

// Prints out the input for debugging.
void ClientUpdatePacket::printAll() {
	for (int i = 0; i < m_inputCount; i++) {
		std::cout << m_input[i] << "\n";
	}
}

// Resets packet to defaults
void ClientUpdatePacket::clear() {
	m_input.clear();
	m_inputCount = 0;
	m_size = 1;
}
