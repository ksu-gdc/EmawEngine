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
	float m_timeSinceLastMessage;

	ClientState* m_serverClientState;
	ClientState* m_currentClientState;
	ClientNetwork* m_network;
	ConnectionPacket* m_pingPacket;
	ClientUpdatePacket* m_updatePacket;
	ServerUpdatePacket* m_serverPacket;

	void sendUpdatePacket();

	void pingServer();
	
	void handleConnetionPacket(char * data);
	void handleServerUpdatePacket(char * data);

public:
	static NetworkManager* getInstance();

	bool connect();
	bool hasServerUpdate();
	ClientState* getClientState();
	std::vector<ClientStateMin*> getOtherClientStates();
	void update(float elapsedTime);
	void addInput(std::string input);
};

