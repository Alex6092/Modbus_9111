#include "ModbusWriteWord.h"
#include "ModbusParser.h"
#include "TcpServer.h"


ModbusWriteWord::ModbusWriteWord(ClientState * client, int transactionId, int protocolId, int unitIdentifier, int wordAddress, int wordValue)
	: ModbusOperation(client, transactionId, protocolId, unitIdentifier)
{
	this->wordAddress = wordAddress;
	this->wordValue = wordValue;
}


ModbusWriteWord::~ModbusWriteWord()
{
}

void ModbusWriteWord::Execute(ModbusVariableSimulation * simulation)
{
	simulation->writeHoldingRegisterValue(wordAddress, wordValue);

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
	sentence[i++] = 0x06;

	// 2 bytes wordAddress :
	sentence[i++] = (wordAddress & 0xFF00) >> 8;
	sentence[i++] = wordAddress & 0x00FF;

	// 2 bytes value :
	sentence[i++] = (wordValue & 0xFF00) >> 8;
	sentence[i++] = wordValue & 0x00FF;

	TcpServer<ModbusParser, ClientState>::Send(getClient(), (char*)sentence, sentenceLength);

	delete sentence;
}