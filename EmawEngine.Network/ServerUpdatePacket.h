// James Tyson
#ifdef EMAWENGINENETWORK_EXPORTS
#define EMAWENGINENETWORK_API __declspec(dllexport)
#else
#define EMAWENGINENETWORK_API __declspec(dllimport)
#endif

#pragma once

#include <vector>
#include <string>
#include "NetworkData.h"

#include <iostream>

// Server to client update packet
class EMAWENGINENETWORK_API ServerUpdatePacket
{
public:
	ServerUpdatePacket();
	ServerUpdatePacket(char * data);
	~ServerUpdatePacket();

	void addMainPlayer(ClientState client);
	void addPlayer(ClientStateMin client);
	char * pack();
	int size();
	void printAll();

private:
	ClientState m_mainPlayer;
	std::vector<ClientStateMin> m_players;
	uint m_pCount;
	int m_size;
};