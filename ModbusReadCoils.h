#pragma once
#include "ModbusOperation.h"
#include "ClientState.h"

class ModbusReadCoils : public ModbusOperation
{
	int startAddress;
	int nbCoil;

public:
	ModbusReadCoils(ClientState * client, int transactionId, int protocolId, int unitIdentifier, int startAddress, int nbCoil);
	~ModbusReadCoils();

	virtual void Execute(ModbusVariableSimulation * simulation);
};

