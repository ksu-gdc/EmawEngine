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
#include "stdafx.h"

#include <iostream>

#define MAX_INPUT_SIZE 10

// CLient to server update message
class EMAWENGINENETWORK_API ClientUpdatePacket
{
public:
	ClientUpdatePacket();
	ClientUpdatePacket(char * data);
	~ClientUpdatePacket();

	void addInput(std::string input);
	char * pack();
	int size();
	void printAll();

private:
	std::vector<std::string> m_input;
	unsigned int m_inputCount;
	int m_size;
};