#pragma once
#include "ModbusOperation.h"
#include "ClientState.h"

class ModbusWriteWord : public ModbusOperation
{
	int wordAddress;
	int wordValue;

public:
	ModbusWriteWord(ClientState * client, int transactionId, int protocolId, int unitIdentifier, int wordAddress, int wordValue);
	~ModbusWriteWord();

	virtual void Execute(ModbusVariableSimulation * simulation);
};

