// James Tyson
#pragma once

#include <string.h>

namespace EmawEngineServer {
	enum PacketTypes {
		CONNECTION_PACKET = 0,
		CLIENT_UPDATE = 1,
		SERVER_UPDATE = 2,
	};

	struct Vector3 {
		float x = 0;
		float y = 0;
		float z = 0;
	};

	const int MAX_PACKET_SIZE = 1000000;
}