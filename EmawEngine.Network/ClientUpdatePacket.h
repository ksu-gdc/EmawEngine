// James Tyson
#include <vector>
#include <string>
#include "NetworkData.h"

#include <iostream>

#define MAX_INPUT_SIZE 10

namespace EmawEngineServer {
	class ClientUpdatePacket
	{
	public:
		__declspec(dllexport) ClientUpdatePacket();
		__declspec(dllexport) ClientUpdatePacket(char * data);
		__declspec(dllexport) ~ClientUpdatePacket();

		__declspec(dllexport) void addInput(std::string input);
		__declspec(dllexport) char * pack();
		__declspec(dllexport) int size();
		__declspec(dllexport) void printAll();

	private:
		std::vector<std::string> m_input;
		unsigned int m_inputCount;
		int m_size;
	};
}