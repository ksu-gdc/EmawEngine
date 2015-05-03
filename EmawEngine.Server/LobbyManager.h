#pragma once

#include <map>
#include <winsock2.h>
#include "Lobby.h"
#include "ServerNetwork.h"

#define MAX_CLIENTS_IN_LOBBY 8

class LobbyManager
{
public:
	LobbyManager();
	~LobbyManager();

	void update();
	Lobby* createNewLobby();
	void addNewClient(uint clientId);
	void registerNetwork(ServerNetwork* network);

private:
	std::map<uint, Lobby> m_lobbies; // lobby id, lobby
	std::map<uint, uint> m_players; // player id, lobby id
	uint getNewLobbyId();
	uint m_lobbyId;
	ServerNetwork* m_network;
};

