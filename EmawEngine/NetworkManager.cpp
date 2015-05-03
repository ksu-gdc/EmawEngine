#include "stdafx.h"
#include "NetworkManager.h"

bool NetworkManager::instanceFlag = false;
NetworkManager* NetworkManager::instance = NULL;

NetworkManager::NetworkManager()
{
}


NetworkManager::~NetworkManager()
{
}

// Returns the instance of our AssetManager
NetworkManager* NetworkManager::getInstance() {
	if (!instanceFlag)
	{
		instance = new NetworkManager();
		instanceFlag = true;
	}
	return instance;
}

bool NetworkManager::connect() {
	m_game = new ClientGame();
	bool temp = m_game->connect();
	return temp;
}

bool NetworkManager::hasServerUpdate() {
	return false;
}

void NetworkManager::sendClientState(ClientState newState) {

}

ClientState* NetworkManager::getServerClientState() {
	return nullptr;
}

void NetworkManager::update(float elapsedTime) {
	m_game->update();
}