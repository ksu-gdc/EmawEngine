#pragma once

#include "NetworkData.h"

namespace EmawEngineServer {
	enum ConnectionMessage {
		INIT_CONNECTION = 0,
		CLOSE_CONNECTION = 1,
		PING_CONNECTION = 2,
	};

	class ConnectionPacket
	{
	public:
		__declspec(dllexport) ConnectionPacket();
		__declspec(dllexport) ConnectionPacket(char * data);
		__declspec(dllexport) ~ConnectionPacket();

		__declspec(dllexport) char * pack();
		__declspec(dllexport) void setType(ConnectionMessage type);
		__declspec(dllexport) int size();

	private:
		ConnectionMessage m_type;
		int m_size;
	};
}