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

// Represents the player data getting sent across the server.
struct EMAWENGINENETWORK_API PlayerData {
		unsigned int id;
		Vector3 position;
		Vector3 orientation;
		bool firing;

		void init(unsigned int new_id, Vector3 new_position, Vector3 new_orientation, bool new_firing) {
			id = new_id;
			position = new_position;
			orientation = new_orientation;
			firing = new_firing;
		}
	};

class EMAWENGINENETWORK_API ServerUpdatePacket
{
public:
	ServerUpdatePacket();
	ServerUpdatePacket(char * data);
	~ServerUpdatePacket();

	void addPlayer(unsigned int id, Vector3 position, Vector3 orientation, bool firing);
	char * pack();
	int size();
	void printAll();

private:
	std::vector<PlayerData> m_players;
	unsigned int m_playerSize;
	unsigned int m_pCount;
	int m_size;
};