#include "ServerUpdatePacket.h"


ServerUpdatePacket::ServerUpdatePacket()
{
	m_size = -1;
}

ServerUpdatePacket::ServerUpdatePacket(char * data) {
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


ServerUpdatePacket::~ServerUpdatePacket()
{
}

void ServerUpdatePacket::addPlayer(Vector3 position, Vector3 orientation, bool firing) {
	m_pPos.push_back(position);
	m_pOri.push_back(orientation);
	m_pFire.push_back(firing);
	m_pCount++;
}

char * ServerUpdatePacket::pack() {
	unsigned int player_size =
		sizeof(Vector3) * 2 +
		sizeof(bool);
	m_size = sizeof(unsigned int) * 2
		+ m_pCount * player_size;
	char * data = new char[m_size];
	char * loc = data;

	// add the packet type
	unsigned int type = 2;
	memcpy(loc, &type, sizeof(unsigned int));
	loc += sizeof(unsigned int);

	// add the number of inputs
	unsigned int count = m_pCount;
	memcpy(loc, &count, sizeof(unsigned int));
	loc += sizeof(unsigned int);

	// copy all of our strings into the array
	const char * temp;
	for (int i = 0; i < m_pCount; i++) {
		temp = m_input[i].c_str();
		memcpy(loc, temp, MAX_INPUT_SIZE);
		loc += MAX_INPUT_SIZE;
	}

	return data;
}

int ServerUpdatePacket::size() {
	return m_size;
}

void ServerUpdatePacket::printAll() {
	for (int i = 0; i < m_inputCount; i++) {
		std::cout << m_input[i] << "\n";
	}
}
