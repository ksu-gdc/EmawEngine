// James Tyson
#pragma once

#include "ServerNetwork.h"
#include "NetworkServices.h"
#include <iostream>

class ServerInstance
{

public:
	ServerInstance(void);
	~ServerInstance(void);

	void listen();
	void receiveFromClients();
	void sendUpdateToAll();

private:

	// IDs for the clients connecting for table in ServerNetwork 
	static unsigned int client_id;

	// The ServerNetwork object 
	ServerNetwork* network;

	// data buffer
	char network_data[MAX_PACKET_SIZE];

	void handleConnectionPacket(char * data);
	void handleClientUpdatePacket(char * data);
};