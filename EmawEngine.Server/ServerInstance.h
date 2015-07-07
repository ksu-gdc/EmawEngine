// James Tyson
#pragma once

#include "ServerNetwork.h"
#include "NetworkServices.h"
#include "LobbyManager.h"
#include <iostream>

class ServerInstance
{

public:
	ServerInstance(void);
	~ServerInstance(void);

	void listen();

private:

	// IDs for the clients connecting for table in ServerNetwork 
	static unsigned int client_id;

	LobbyManager* lobbyManager;
	ServerNetwork* network;
};