// James Tyson
#ifdef EMAWENGINENETWORK_EXPORTS
#define EMAWENGINENETWORK_API __declspec(dllexport)
#else
#define EMAWENGINENETWORK_API __declspec(dllimport)
#endif

#pragma once

#include <string.h>
#include "stdafx.h"

enum EMAWENGINENETWORK_API PacketTypes {
	CONNECTION_PACKET = 0,
	CLIENT_UPDATE = 1,
	SERVER_UPDATE = 2,
};

struct EMAWENGINENETWORK_API Vector3 {
	float x = 0;
	float y = 0;
	float z = 0;
};

const int MAX_PACKET_SIZE = 1000000;