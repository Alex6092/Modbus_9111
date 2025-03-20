#pragma once
#include "ModbusOperation.h"
#include "ClientState.h"

class ModbusReadDigitalInputs : public ModbusOperation
{
	int startAddress;
	int nbInput;
public:
	ModbusReadDigitalInputs(ClientState * client, int transactionId, int protocolId, int unitIdentifier, int startAddress, int nbInput);
	~ModbusReadDigitalInputs();

	virtual void Execute(ModbusVariableSimulation * simulation);
};

