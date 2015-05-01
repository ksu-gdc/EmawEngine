// James Tyson
#include "ClientGame.h" 

ClientGame::ClientGame(void)
{
	// TODO: add time outs and reconnects
	connect();
}

bool ClientGame::connect() {
	network = new ClientNetwork();

	// Send init packet
	ConnectionPacket packet = ConnectionPacket();
	packet.setType(INIT_CONNECTION);

	char * packet_data = packet.pack();
	int packet_size = packet.size();

	if (NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size))
		return true;

	return false;
}

void ClientGame::sendUpdatePacket()
{
	ClientUpdatePacket packet = ClientUpdatePacket();
	packet.addInput("testMsg");
	packet.addInput("test2Msg");

	char * packet_data = packet.pack();
	int packet_size = packet.size();

	int sent = NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientGame::update()
{
	int data_length = network->receivePackets(network_data);
	if (data_length <= 0)
	{
		//no data recieved
		return;
	}

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
void ClientGame::handleConnetionPacket(char * data) {
	printf("Client received init packet from server\n");
	ConnectionPacket packet = ConnectionPacket(network_data);
}

// Handles a server update packet
void ClientGame::handleServerUpdatePacket(char * data) {
	printf("Client received server update packet from server\n");
	ServerUpdatePacket packet = ServerUpdatePacket(network_data);
	packet.printAll();
}