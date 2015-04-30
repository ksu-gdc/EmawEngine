// James Tyson
#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <Windows.h>

namespace EmawEngineServer {
	class NetworkServices
	{
	public:
		static int sendMessage(SOCKET curSocket, char* message, int messageSize);
		static int receiveMessage(SOCKET curSocket, char* buffer, int bufsize);
	};
}