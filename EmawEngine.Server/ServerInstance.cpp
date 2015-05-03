// James Tyson
#include "ServerInstance.h"

unsigned int ServerInstance::client_id;

ServerInstance::ServerInstance(void)
{
	// id's to assign clients for our table
	client_id = 0;

	// set up the server network to listen 
	network = new ServerNetwork();

	lobbyManager = new LobbyManager();
}

void ServerInstance::listen()
{
	// get new clients
	if (network->acceptNewClient(client_id))
	{
		printf("client %d has been connected to the server\n", client_id);
		lobbyManager->addNewClient(client_id);

		client_id++;
	}
}