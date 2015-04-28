#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "NetworkData.h"

class ClientGame
{

public:

	ClientGame();
	~ClientGame(void);

	ClientNetwork* network;
};
