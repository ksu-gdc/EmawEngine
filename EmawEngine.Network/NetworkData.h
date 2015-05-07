// James Tyson
#ifdef EMAWENGINENETWORK_EXPORTS
#define EMAWENGINENETWORK_API __declspec(dllexport)
#else
#define EMAWENGINENETWORK_API __declspec(dllimport)
#endif

#pragma once

#include <string.h>
#include "Types.h"

enum EMAWENGINENETWORK_API PacketTypes {
	CONNECTION_PACKET = 0,
	CLIENT_UPDATE = 1,
	SERVER_UPDATE = 2,
};

struct EMAWENGINENETWORK_API Vector3 {
	float x = 0;
	float y = 0;
	float z = 0;

	void init(float new_x, float new_y, float new_z) {
		x = new_x;
		y = new_y;
		z = new_z;
	}
};

struct EMAWENGINENETWORK_API ClientState {
	uint id;
	Vector3 position;
	Vector3 orientation;
	uint health;
	uint ammo;

	void init(uint new_id, Vector3 new_position, Vector3 new_orientation, uint new_health, uint new_ammo) {
		id = new_id;
		position = new_position;
		orientation = new_orientation;
		health = new_health;
		ammo = new_ammo;
	}
};

struct EMAWENGINENETWORK_API ClientStateMin {
	uint id;
	Vector3 position;
	Vector3 orientation;
	u8 flags;  /* Bits in order of 76543210:
	*  0 - Firing
	*  1 - Moving forward
	*  2 - Moving backwards
	*  3 - Moving right
	*  4 - Moving left
	*  5 - Jumping
	*  6 - Crouching
	*  7 - Dead
	*/

	void init(u8 new_id, Vector3 new_position, Vector3 new_orientation, u8 new_flags) {
		id = new_id;
		position = new_position;
		orientation = new_orientation;
		flags = new_flags;
	}
};

struct EMAWENGINENETWORK_API WorldState {
	int team1Score;
	int team2Score;
	int time;
};

const int MAX_PACKET_SIZE = 1000000;