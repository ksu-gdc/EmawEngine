// James Tyson
#ifdef EMAWENGINENETWORK_EXPORTS
#define EMAWENGINENETWORK_API __declspec(dllexport)
#else
#define EMAWENGINENETWORK_API __declspec(dllimport)
#endif

#pragma once

#include "NetworkData.h"
#include "stdafx.h"

enum EMAWENGINENETWORK_API ConnectionMessage {
	INIT_CONNECTION = 0,
	CLOSE_CONNECTION = 1,
	PING_CONNECTION = 2,
};

class EMAWENGINENETWORK_API ConnectionPacket
{
public:
	ConnectionPacket();
	ConnectionPacket(char * data);
	~ConnectionPacket();

	char * pack();
	void setType(ConnectionMessage type);
	int size();

private:
	ConnectionMessage m_type;
	int m_size;
};