#include "ModbusReadCoils.h"
#include "TcpServer.h"
#include "ModbusParser.h"
#include <queue>


ModbusReadCoils::ModbusReadCoils(ClientState * client, int transactionId, int protocolId, int unitIdentifier, int startAddress, int nbCoil)
	: ModbusOperation(client, transactionId, protocolId, unitIdentifier)
{
	this->startAddress = startAddress;
	this->nbCoil = nbCoil;
}


ModbusReadCoils::~ModbusReadCoils()
{
}

void ModbusReadCoils::Execute(ModbusVariableSimulation * simulation)
{
	std::deque<bool> values;

	for (int i = 0; i < nbCoil; i++)
		values.push_back(simulation->readCoilValue(startAddress + i));

	std::deque<char> sentenceData;
	int byteNb = 0;
	for (int i = 0; i < values.size(); i++)
	{
		if (i % 8 == 0)
		{
			sentenceData.push_back(0x00);
			byteNb++;
		}

		sentenceData[byteNb - 1] |= ((values[i] ? 1 : 0) << (i % 8));
	}

	// Process answer bytes number :
	int dataLength = sentenceData.size();

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
	sentence[i++] = 0x01;
	// 1 byte data length :
	sentence[i++] = dataLength & 0xFF;

	while (sentenceData.size() > 0)
	{
		char value = sentenceData.front();
		sentenceData.pop_front();

		// 1 bytes for 8 coils :
		sentence[i++] = value & 0x00FF;
	}

	TcpServer<ModbusParser, ClientState>::Send(getClient(), (char*)sentence, sentenceLength);

	delete sentence;
}