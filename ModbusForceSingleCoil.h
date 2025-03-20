#pragma once
#include "ModbusOperation.h"
#include "ClientState.h"

class ModbusForceSingleCoil : public ModbusOperation
{
	int coilAddress;
	bool coilValue;

public:
	ModbusForceSingleCoil(ClientState * client, int transactionId, int protocolId, int unitIdentifier, int coilAddress, bool coilValue);
	~ModbusForceSingleCoil();

	virtual void Execute(ModbusVariableSimulation * simulation);
};

