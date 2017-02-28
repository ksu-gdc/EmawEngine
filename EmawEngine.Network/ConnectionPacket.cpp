#include "ConnectionPacket.h"
#include "stdafx.h"

// Default Constructor.
ConnectionPacket::ConnectionPacket()
{
	m_type = PING_CONNECTION;
	m_size = sizeof(unsigned int) + sizeof(unsigned int);
}

// Constructor that depacks packet data.
ConnectionPacket::ConnectionPacket(char * data) {
	m_size = sizeof(unsigned int) + sizeof(unsigned int);

	char * loc = data;
	//ignore first unsigned int, it is packet type
	loc += sizeof(unsigned int);
	memcpy(&m_type, loc, sizeof(unsigned int));
	loc += sizeof(unsigned int);
}

// Default Destructor.
ConnectionPacket::~ConnectionPacket()
{
}

// Packs the packet data.
char * ConnectionPacket::pack() {
	char * data = new char[sizeof(unsigned int) + sizeof(unsigned int)];
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

// Sets the ConnectionMessage type of the packet.
void ConnectionPacket::setType(ConnectionMessage type) {
	m_type = type;
}

// Gets the ConnectionMessage type of the packet.
ConnectionMessage ConnectionPacket::getType() {
	return m_type;
}

// Gets the size of the packet.
int ConnectionPacket::size() {
	return m_size;
}
