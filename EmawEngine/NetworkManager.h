#pragma once

#include "NetworkServices.h"
#include "ClientGame.h"

class NetworkManager
{
private:
	NetworkManager();
	~NetworkManager();
	// Statics
	static bool instanceFlag;
	static NetworkManager *instance;

	int m_clientId;
	ClientGame * m_game;

public:
	static NetworkManager* getInstance();

	bool connect();
	bool hasServerUpdate();
	void sendClientState(ClientState newState);
	ClientState* getServerClientState();
	void update(float elapsedTime);

};

