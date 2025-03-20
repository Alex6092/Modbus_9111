#include "ModbusForceSingleCoil.h"
#include "TcpServer.h"
#include "ModbusParser.h"



ModbusForceSingleCoil::ModbusForceSingleCoil(ClientState * client, int transactionId, int protocolId, int unitIdentifier, int coilAddress, bool coilValue)
	: ModbusOperation(client, transactionId, protocolId, unitIdentifier)
{
	this->coilAddress = coilAddress;
	this->coilValue = coilValue;
}


ModbusForceSingleCoil::~ModbusForceSingleCoil()
{
}

void ModbusForceSingleCoil::Execute(ModbusVariableSimulation * simulation)
{
	simulation->writeCoilValue(coilAddress, coilValue);

	int sentenceLength = 12;
	int modbusLength = 6;
	unsigned char * sentence = new unsigned char[sentenceLength];

	int i = 0;
	// 2 bytes transactionId :
	sentence[i++] = (getTransactionId() & 0xFF00) >> 8;
	sentence[i++] = getTransactionId() & 0x00FF;
	// 2 bytes protocolId :
	sentence[i++] = (getProtocolId() & 0xFF00) >> 8;
	sentence[i++] = getProtocolId() & 0x00FF;
	// 2 bytes data's length :
	sentence[i++] = (modbusLength & 0xFF00) >> 8;
	sentence[i++] = modbusLength & 0x00FF;
	// 1 byte unitIdentifier :
	sentence[i++] = getUnitIdentifier() & 0x00FF;
	// 1 byte function :
	sentence[i++] = 0x05;

	// 2 bytes wordAddress :
	sentence[i++] = (coilAddress & 0xFF00) >> 8;
	sentence[i++] = coilAddress & 0x00FF;

	// 2 bytes value :
	sentence[i++] = (coilValue & 0xFF00) >> 8;
	sentence[i++] = coilValue & 0x00FF;

	TcpServer<ModbusParser, ClientState>::Send(getClient(), (char*)sentence, sentenceLength);
	
	delete sentence;
}