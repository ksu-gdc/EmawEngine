// James Tyson
#pragma once

#include "ServerNetwork.h"
#include "NetworkData.h"
#include "ClientUpdatePacket.h"
#include "ConnectionPacket.h"
#include "ServerUpdatePacket.h"
#include <iostream>

class ServerGame
{

public:
	ServerGame(void);
	~ServerGame(void);

	void update();
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