// EmawEngine.Network.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "EmawEngine.Network.h"


// This is an example of an exported variable
EMAWENGINENETWORK_API int nEmawEngineNetwork=0;

// This is an example of an exported function.
EMAWENGINENETWORK_API int fnEmawEngineNetwork(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see EmawEngine.Network.h for the class definition
CEmawEngineNetwork::CEmawEngineNetwork()
{
	return;
}
