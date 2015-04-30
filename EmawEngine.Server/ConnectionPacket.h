#pragma once

#include "NetworkData.h"

enum ConnectionMessage {
	INIT_CONNECTION = 0,
	CLOSE_CONNECTION = 1,
	PING_CONNECTION = 2,
};

class ConnectionPacket
{
public:
	ConnectionPacket();
	ConnectionPacket(char * data);
	~ConnectionPacket();

	char * pack();
	void setType(ConnectionMessage type);
	int size();

private:
	ConnectionMessage m_type;
	int m_size;
};

