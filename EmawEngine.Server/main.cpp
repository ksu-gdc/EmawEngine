// James Tyson
#include "ServerInstance.h"

ServerInstance * server;

int main()
{
	// initialize the server
	server = new ServerInstance();

	while (true)
	{
		server->listen();
	}
}

