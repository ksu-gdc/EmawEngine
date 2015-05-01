// James Tyson
#ifdef EMAWENGINENETWORK_EXPORTS
#define EMAWENGINENETWORK_API __declspec(dllexport)
#else
#define EMAWENGINENETWORK_API __declspec(dllimport)
#endif

#pragma comment(lib, "Ws2_32.lib")
#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include "NetworkData.h"
#include "Packets.h"


class EMAWENGINENETWORK_API NetworkServices
{
public:
	static int sendMessage(SOCKET curSocket, char* message, int messageSize);
	static int receiveMessage(SOCKET curSocket, char* buffer, int bufsize);
};