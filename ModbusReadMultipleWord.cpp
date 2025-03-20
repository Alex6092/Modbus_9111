#include "ModbusReadMultipleWord.h"
#include <queue>
#include "ModbusParser.h"
#include "TcpServer.h"


ModbusReadMultipleWord::ModbusReadMultipleWord(ClientState * client, int transactionId, int protocolId, int unitIdentifier, unsigned int startAddress, unsigned int nbWord)
	: ModbusOperation(client, transactionId, protocolId, unitIdentifier)
{
	this->startAddress = startAddress;
	this->nbWord = nbWord;
}


ModbusReadMultipleWord::~ModbusReadMultipleWord()
{
}

void ModbusReadMultipleWord::Execute(ModbusVariableSimulation * simulation)
{
	std::queue<int> values;

	for (int i = 0; i < nbWord; i++)
		values.push(simulation->readHoldingRegisterValue(startAddress + i));

	int dataLength = (2 * nbWord);
	int sentenceLength = 8 + dataLength + 1;
	int modbusLength = 2 + dataLength + 1;
	
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
	sentence[i++] = 0x03;
	// 1 byte data length :
	sentence[i++] = dataLength & 0xFF;

	while (values.size() > 0)
	{
		int value = values.front();
		values.pop();

		// 2 bytes for a value :
		sentence[i++] = (value & 0xFF00) >> 8;
		sentence[i++] = value & 0x00FF;
	}

	TcpServer<ModbusParser, ClientState>::Send(getClient(), (char*)sentence, sentenceLength);

	delete sentence;
}
