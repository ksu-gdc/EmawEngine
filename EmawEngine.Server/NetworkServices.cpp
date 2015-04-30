// James Tyson
#include "NetworkServices.h"

using namespace EmawEngineServer;

namespace EmawEngineServer {
	// Sends a message to the given socket.
	int NetworkServices::sendMessage(SOCKET curSocket, char * message, int messageSize)
	{
		return send(curSocket, message, messageSize, 0);
	}

	// Attempts to listen for a message from the given socket.
	int NetworkServices::receiveMessage(SOCKET curSocket, char * buffer, int bufSize)
	{
		return recv(curSocket, buffer, bufSize, 0);
	}
}