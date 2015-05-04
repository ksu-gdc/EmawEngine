#include "stdafx.h"
#include "NetworkManager.h"

bool NetworkManager::instanceFlag = false;
NetworkManager* NetworkManager::instance = NULL;

NetworkManager::NetworkManager()
{
	m_hasServerUpdate = false;
	m_currentClientState = new ClientState();
	m_serverClientState = new ClientState();
	m_updatePacket = new ClientUpdatePacket();
}


NetworkManager::~NetworkManager()
{
}

// Returns the instance of our AssetManager
NetworkManager* NetworkManager::getInstance() {
	if (!instanceFlag)
	{
		instance = new NetworkManager();
		instanceFlag = true;
	}
	return instance;
}

bool NetworkManager::connect() {
	m_network = new ClientNetwork();

	// Send init packet
	ConnectionPacket packet = ConnectionPacket();
	packet.setType(INIT_CONNECTION);

	char * packet_data = packet.pack();
	int packet_size = packet.size();

	if (NetworkServices::sendMessage(m_network->ConnectSocket, packet_data, packet_size))
		return true;

	return false;
}

void pingServer() {
	char network_data[MAX_PACKET_SIZE];
}

bool NetworkManager::hasServerUpdate() {
	return m_hasServerUpdate;
}

void NetworkManager::sendClientState(ClientState newState) {

}

void NetworkManager::addInput(std::string input) {
	m_stateChanged = true;
	m_updatePacket->addInput(input);
}

// Accessor for the server client state
ClientState* NetworkManager::getServerClientState() {
	return m_serverClientState;
}

void NetworkManager::update()
{
	int data_length = m_network->receivePackets(network_data);
	if (data_length <= 0)
	{
		//no data recieved
		sendUpdatePacket();
		m_hasServerUpdate = false;
		return;
	}

	m_hasServerUpdate = true;
	
	unsigned int type = *((unsigned int *)network_data);
	switch (type) {

	case CONNECTION_PACKET:
		handleConnetionPacket(network_data);
		break;

	case SERVER_UPDATE:
		handleServerUpdatePacket(network_data);
		break;

	default:
		printf("error in packet types\n");
		break;
	}

	sendUpdatePacket();
}

// Handles a connection packet
void NetworkManager::handleConnetionPacket(char * data) {
	printf("Client received init packet from server\n");
	ConnectionPacket packet = ConnectionPacket(network_data);
}

// Handles a server update packet
void NetworkManager::handleServerUpdatePacket(char * data) {
	printf("Client received server update packet from server\n");
	ServerUpdatePacket packet = ServerUpdatePacket(network_data);
	packet.printAll();
}

void NetworkManager::sendUpdatePacket()
{
	if (!m_stateChanged) {
		// no update to send
		return;
	}

	char * packet_data = m_updatePacket->pack();
	int packet_size = m_updatePacket->size();

	int sent = NetworkServices::sendMessage(m_network->ConnectSocket, packet_data, packet_size);
	if (sent) {
		m_updatePacket->clear();
		m_stateChanged = false;
	}
}