#include "ConnectionPacket.h"


ConnectionPacket::ConnectionPacket()
{
	m_type = PING_CONNECTION;
	m_size = sizeof(ConnectionMessage) + sizeof(unsigned int);
}

ConnectionPacket::ConnectionPacket(char * data) {
	m_type = PING_CONNECTION;
	m_size = sizeof(ConnectionMessage) + sizeof(unsigned int);

	char * loc = data;
	//ignore first unsigned int, it is type
	loc += sizeof(unsigned int);
	memcpy(&m_type, loc, sizeof(unsigned int));
	loc += sizeof(unsigned int);
}

ConnectionPacket::~ConnectionPacket()
{
}

char * ConnectionPacket::pack() {
	char data[sizeof(ConnectionMessage) + sizeof(unsigned int)];
	char * loc = data;

	// Add the packet type
	unsigned int type = CONNECTION_PACKET;
	memcpy(loc, &type, sizeof(unsigned int));
	loc += sizeof(unsigned int);

	// Add the message type
	unsigned int msg = m_type;
	memcpy(loc, &msg, sizeof(unsigned int));

	return data;
}

void ConnectionPacket::setType(ConnectionMessage type) {
	m_type = type;
}

int ConnectionPacket::size() {
	return m_size;
}
