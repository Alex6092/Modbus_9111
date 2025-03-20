#pragma once
#include "ModbusOperation.h"

class ModbusReadMultipleWord :
	public ModbusOperation
{
	unsigned int startAddress;
	unsigned int nbWord;

public:
	ModbusReadMultipleWord(ClientState * client, int transactionId, int protocolId, int unitIdentifier, unsigned int startAddress, unsigned int nbWord);
	~ModbusReadMultipleWord();

	virtual void Execute(ModbusVariableSimulation * simulation);
};

