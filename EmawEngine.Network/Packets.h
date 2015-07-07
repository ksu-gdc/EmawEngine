#ifdef EMAWENGINENETWORK_EXPORTS
#define EMAWENGINENETWORK_API __declspec(dllexport)
#else
#define EMAWENGINENETWORK_API __declspec(dllimport)
#endif

#pragma once

#include "stdafx.h"
#include "ClientUpdatePacket.h"
#include "ConnectionPacket.h"
#include "ServerUpdatePacket.h"