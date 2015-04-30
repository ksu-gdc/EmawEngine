// James Tyson
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "ClientUpdatePacket.h"
#include "ConnectionPacket.h"
#include "ServerUpdatePacket.h"
#include "NetworkData.h"
#include <iostream>

class ClientGame
{

public:

	ClientGame();
	~ClientGame(void);

	ClientNetwork* network;

	void sendUpdatePacket();

	char network_data[MAX_PACKET_SIZE];

	void update();
	bool connect();

private:
	void handleConnetionPacket(char * data);
	void handleServerUpdatePacket(char * data);
};
