#include "ServerGame.h"

// Default Constructor
ServerGame::ServerGame()
{
}

// Default Desrtuctor.
ServerGame::~ServerGame()
{
}

// Loads the game.
void ServerGame::load() {

}

// Updates the game.
void ServerGame::update() {

}

// Adds a new player to the game.  Called only when a player connects.
void ServerGame::addPlayer(uint id) {
	// Create our new client state objects
	ClientState* c = new ClientState();
	c->id = id;
	ClientStateMin* cm = new ClientStateMin();
	cm->id = id;
	// Add them to our list of players
	m_players.insert(std::pair <uint, ClientState*>(id, c));
	m_playersMin.insert(std::pair <uint, ClientStateMin*>(id, cm));

	// TODO: Add them to game logic here
}

// Removes a player from the game.  Called only when a player disconnects.
void ServerGame::removePlayer(uint id) {
	if (m_players.find(id) != m_players.end()) {
		m_players.erase(id);
	}
	if (m_playersMin.find(id) != m_playersMin.end()) {
		m_playersMin.erase(id);
	}

	//TODO: Remove them from game logic here.
}

// Gets a specific client state
ClientState* ServerGame::getClientState(uint id) {
	if (m_players.find(id) != m_players.end()) {
		return m_players[id];
	}
	return 0;
}

// Gets a specific ClientStateMin
ClientStateMin* ServerGame::getClientStateMin(uint id) {
	if (m_playersMin.find(id) != m_playersMin.end()) {
		return m_playersMin[id];
	}
	return 0;
}

// Gets a list of ClientStateMins for all of the players in the game
std::vector<ClientStateMin*> ServerGame::getAllClients() {
	std::vector<ClientStateMin*> v;
	for (std::map<uint, ClientStateMin*>::iterator it = m_playersMin.begin(); it != m_playersMin.end(); ++it) {
		v.push_back(it->second);
	}
	return v;
}