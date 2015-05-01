// James Tyson
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include <iostream>

#include "NetworkServices.h"

class ClientGame
{

public:

	ClientGame();
	~ClientGame(void);

	ClientNetwork* network;

	void sendUpdatePacket();

	char network_data[EmawEngineServer::MAX_PACKET_SIZE];

	void update();
	bool connect();

private:
	void handleConnetionPacket(char * data);
	void handleServerUpdatePacket(char * data);
};
