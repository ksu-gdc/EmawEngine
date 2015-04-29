#pragma once

#include <string.h>

#define MAX_PACKET_SIZE 1000000

enum PacketTypes {
	INIT_CONNECTION = 0,
	CLOSE_CONNECTION = 1,
	CLIENT_UPDATE = 2,
	SERVER_UPDATE = 3,
};

struct Packet {

	unsigned int packet_type;
	unsigned int length;

	void serialize(char * data) {
		memcpy(data, this, length);
	}

	void deserialize(char * data) {
		memcpy(this, data, length);
	}
};

struct Vector3 {
	float x = 0;
	float y = 0;
	float z = 0;
};