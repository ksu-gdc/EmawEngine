#include "ClientGame.h" 

ClientGame::ClientGame(void)
{
	// TODO: add time outs and reconnects
	connect();
}

bool ClientGame::connect() {
	network = new ClientNetwork();

	// send init packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;

	packet.serialize(packet_data);

	if (NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size))
		return true;

	return false;
}

void ClientGame::sendActionPackets()
{
	ClientPacket packet = ClientPacket();
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

	int i = 0;
	unsigned int * type = (unsigned int *)network_data;
	ServerUpdatePacket packet;
	switch (*type) {

	case 0: // INIT CONNECTION
		printf("client received init packet from server\n");
		sendActionPackets();
		break;

	case 3: // SERVER UPDATE
		printf("client received server update packet from server\n");
		packet = ServerUpdatePacket(network_data);
		packet.printAll();
		sendActionPackets();
		break;

	default:
		printf("error in packet types\n");
		break;
	}
}