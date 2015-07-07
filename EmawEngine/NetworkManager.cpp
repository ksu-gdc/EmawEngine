#include "stdafx.h"
#include "NetworkManager.h"

bool NetworkManager::instanceFlag = false;
NetworkManager* NetworkManager::instance = NULL;

// Default Constructor.
NetworkManager::NetworkManager()
{
	m_hasServerUpdate = false;
	m_currentClientState = new ClientState();
	m_serverClientState = new ClientState();
	m_updatePacket = new ClientUpdatePacket();
	m_serverPacket = new ServerUpdatePacket();
	m_timeSinceLastMessage = 0;

	m_pingPacket = new ConnectionPacket();
	m_pingPacket->setType(PING_CONNECTION);
}

// Default Destructor.
NetworkManager::~NetworkManager()
{
}

// Returns the instance of our NetworkManager
NetworkManager* NetworkManager::getInstance() {
	if (!instanceFlag)
	{
		instance = new NetworkManager();
		instanceFlag = true;
	}
	return instance;
}

// Connects to the server.
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

// Sends a packet to the server just to ping it and let the server know we are still alive.
void NetworkManager::pingServer() {
	// Send ping packet
	char * packet_data = m_pingPacket->pack();
	int packet_size = m_pingPacket->size();

	if (NetworkServices::sendMessage(m_network->ConnectSocket, packet_data, packet_size))
		m_timeSinceLastMessage = 0;
}

// Gets if there was a server update.
bool NetworkManager::hasServerUpdate() {
	return m_hasServerUpdate;
}

// Adds an input from the user to the packet to send to the server.
void NetworkManager::addInput(std::string input) {
	m_stateChanged = true;
	m_updatePacket->addInput(input);
}

// Accessor for the server client state
ClientState* NetworkManager::getClientState() {
	return m_serverPacket->getPlayer();
}

// Gets the client state of all of the other players
std::vector<ClientStateMin*> NetworkManager::getOtherClientStates() {
	return m_serverPacket->getOtherPlayers();
}

void NetworkManager::update(float elapsedTime)
{
	m_timeSinceLastMessage += elapsedTime;

	int data_length = m_network->receivePackets(network_data);
	if (data_length > 0) {
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
	}
	else {
		// No data received
		m_hasServerUpdate = false;
	}

	sendUpdatePacket();
}

// Handles a connection packet.
void NetworkManager::handleConnetionPacket(char * data) {
	printf("Client received init packet from server\n");
	ConnectionPacket packet = ConnectionPacket(data);
}

// Handles a server update packet.
void NetworkManager::handleServerUpdatePacket(char * data) {
	printf("Client received server update packet from server\n");
	m_serverPacket = new ServerUpdatePacket(data);
	m_serverPacket->printAll();
}

// Sends an packet to the server.
void NetworkManager::sendUpdatePacket()
{
	if (m_timeSinceLastMessage >= 1000)
		pingServer();
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
		m_timeSinceLastMessage = 0;
	}
}