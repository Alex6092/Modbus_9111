#include "ModbusOperation.h"



ModbusOperation::ModbusOperation(ClientState * client, int transactionId, int protocolId, int unitIdentifier)
{
	this->client = client;
	this->transactionId = transactionId;
	this->protocolId = protocolId;
	this->unitIdentifier = unitIdentifier;
}


ModbusOperation::~ModbusOperation()
{
}
