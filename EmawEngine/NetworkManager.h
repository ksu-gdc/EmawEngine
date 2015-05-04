#pragma once

#include "NetworkServices.h"
#include "ClientNetwork.h"

class NetworkManager
{
private:
	NetworkManager();
	~NetworkManager();
	// Statics
	static bool instanceFlag;
	static NetworkManager *instance;

	char network_data[MAX_PACKET_SIZE];
	int m_clientId;
	bool m_hasServerUpdate;
	bool m_stateChanged;

	ClientState* m_serverClientState;
	ClientState* m_currentClientState;
	ClientNetwork* m_network;
	ClientUpdatePacket* m_updatePacket;

	void sendUpdatePacket();
	void pingServer();
	
	void handleConnetionPacket(char * data);
	void handleServerUpdatePacket(char * data);

public:
	static NetworkManager* getInstance();

	bool connect();
	bool hasServerUpdate();
	void sendClientState(ClientState newState);
	ClientState* getServerClientState();
	void update();
	void addInput(std::string input);
};

