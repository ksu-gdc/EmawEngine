#pragma once

#include "NetworkData.h"

class NetworkPackager
{
public:
	NetworkPackager();
	~NetworkPackager();

	void createPacket(PacketTypes type);
	
};

