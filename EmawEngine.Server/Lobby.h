#pragma once

#include <vector>
#include <winsock2.h>
#include "NetworkData.h"
#include "Packets.h"
#include "ServerNetwork.h"

class Lobby
{
public:
	Lobby();
	Lobby(uint id, ServerNetwork* network);
	~Lobby();

	void update();
	void receiveFromClients();
	uint addClient(uint clientId);
	u8 getPlayerCount();
	uint getId();
private:
	u8 m_playerCount;
	uint m_id;
	ServerNetwork* m_network;

	// table to keep track of each client's socket
	std::vector<uint> m_playerIds;

	// data buffer
	char network_data[MAX_PACKET_SIZE];

	void handleConnectionPacket(char * data);
	void handleClientUpdatePacket(char * data);

	void sendUpdateToAll();
};

