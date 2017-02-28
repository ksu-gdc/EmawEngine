#pragma once

#include "NetworkData.h"
#include <map>
#include <vector>

class ServerGame
{
public:
	ServerGame();
	~ServerGame();

	void load();
	void update();
	void addPlayer(uint id);
	void removePlayer(uint id);
	ClientState* getClientState(uint id);
	ClientStateMin* getClientStateMin(uint id);
	std::vector<ClientStateMin*> getAllClients();

private:
	std::map<uint, ClientState*> m_players;
	std::map<uint, ClientStateMin*> m_playersMin;
};

