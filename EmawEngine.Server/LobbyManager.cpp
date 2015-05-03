#include "LobbyManager.h"


LobbyManager::LobbyManager()
{
}


LobbyManager::~LobbyManager()
{
}

void LobbyManager::registerNetwork(ServerNetwork* network) {
	m_network = network;
}

// Update all of the lobbies
void LobbyManager::update() {
	std::map<uint, Lobby>::iterator iter;
	for (iter = m_lobbies.begin(); iter != m_lobbies.end(); iter++)
	{
		iter->second.update();
	}
}

// Creates a new lobby
Lobby* LobbyManager::createNewLobby() {
	Lobby* l = new Lobby(getNewLobbyId(), m_network);
	m_lobbies.insert(std::pair<uint, Lobby>(l->getId(), *l));
	return l;
}

// Gets a new lobby id
uint LobbyManager::getNewLobbyId() {
	return m_lobbyId++;
}

// Attempts to add new clients to existing lobbies, up to the MAX_CLIENTS_IN_LOBBY.
// If no lobby can be found a new one will be created.
void LobbyManager::addNewClient(uint clientId) {
	std::map<uint, Lobby>::iterator iter;
	for (iter = m_lobbies.begin(); iter != m_lobbies.end(); iter++)
	{
		if (iter->second.getPlayerCount() < MAX_CLIENTS_IN_LOBBY) {
			// Add the player to the lobby
			iter->second.addClient(clientId);
			// Add the player and lobby id to the player table
			m_players.insert(std::pair<uint, uint>(clientId, iter->first)); // client id, lobby id
			return;
		}
	}
	// If the client was not added to a lobby, create a new one
	uint id = createNewLobby()->addClient(clientId);
	m_players.insert(std::pair<uint, uint>(clientId, id));
}