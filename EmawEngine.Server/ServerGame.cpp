#include "ServerGame.h"

unsigned int ServerGame::client_id;

ServerGame::ServerGame(void)
{
	// id's to assign clients for our table
	client_id = 0;

	// set up the server network to listen 
	network = new ServerNetwork();
}

void ServerGame::update()
{
	// get new clients
	if (network->acceptNewClient(client_id))
	{
		printf("client %d has been connected to the server\n", client_id);

		client_id++;
	}

	receiveFromClients();
}


void ServerGame::receiveFromClients()
{

	Packet packet;

	// go through all clients
	std::map<unsigned int, SOCKET>::iterator iter;

	for (iter = network->sessions.begin(); iter != network->sessions.end(); iter++)
	{
		int data_length = network->receiveData(iter->first, network_data);

		if (data_length <= 0)
		{
			//no data recieved
			continue;
		}

		int i = 0;
		unsigned int * type = (unsigned int *)network_data;
		ClientPacket packet;
		switch (*type) {

			case 0: // INIT CONNECTION
				printf("server received init packet from client\n");
				sendActionPackets();
				break;

			case 2: // CLIENT UPDATE
				printf("server received action event packet from client\n");
				packet = ClientPacket(network_data);
				packet.printAll();
				sendActionPackets();
				break;

			default:
				printf("error in packet types\n");
				break;
		}
	}
}

void ServerGame::sendActionPackets()
{
	ServerUpdatePacket packet = ServerUpdatePacket();
	Vector3 pos1; pos1.x = 1; pos1.y = 2; pos1.z = 3;
	Vector3 pos2; pos2.x = -1; pos2.y = -2; pos2.z = -3;
	packet.addPlayer(0, pos1, pos2, true);
	packet.addPlayer(1, pos2, pos1, false);
	char * packet_data = packet.pack();
	int packet_size = packet.size();

	network->sendToAll(packet_data, packet_size);
}