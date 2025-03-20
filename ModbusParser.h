#pragma once

#include "Parser.h"
#include "ThreadSafeQueue.h"

class ModbusOperation;

class ModbusParser : public Parser<ClientState>
{
	ThreadSafeQueue<ModbusOperation *> operations;

public:
	ModbusParser();
	~ModbusParser();

	void parse(ClientState * client, std::vector<unsigned char> & receivedPacket);
	void parse(SOCKET sock, unsigned char * buf, int length);

	ThreadSafeQueue<ModbusOperation *> & getOperation();
};

