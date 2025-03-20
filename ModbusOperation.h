#pragma once

#include "ModbusVariableSimulation.h"
#include "ClientState.h"

class ModbusOperation
{
private:
	ClientState * client;
	int transactionId;
	int protocolId;
	int unitIdentifier;

public:
	ModbusOperation(ClientState * client, int transactionId, int protocolId, int unitIdentifier);
	~ModbusOperation();

	virtual void Execute(ModbusVariableSimulation * addressSpace) = 0;
	inline ClientState * getClient() { return client; }
	inline int getTransactionId() { return transactionId; }
	inline int getProtocolId() { return protocolId; }
	inline int getUnitIdentifier() { return unitIdentifier; }
};

