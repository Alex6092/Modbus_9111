#include "ModbusParser.h"
#include <iostream>

#include "ModbusReadMultipleWord.h"
#include "ModbusWriteWord.h"
#include "ModbusReadCoils.h"
#include "ModbusForceSingleCoil.h"
#include "ModbusReadDigitalInputs.h"

#define LENGTH_IDX 4
#define UNIT_IDENTIFIER_IDX 6
#define FUNCTION_IDX 7

ModbusParser::ModbusParser()
{
}


ModbusParser::~ModbusParser()
{
}

void ModbusParser::parse(ClientState * client, std::vector<unsigned char> & receivedPacket)
{
	std::vector<unsigned char> & buffer = client->getBuffer();

	for (int i = 0; i < receivedPacket.size(); i++)
	{
		unsigned char c = receivedPacket[i];
		buffer.push_back(c);
	}

	bool hasDataToParse = true;

	while (hasDataToParse)
	{
		if (buffer.size() >= 6)
		{
			int dataSize = (buffer[LENGTH_IDX] << 8) | buffer[LENGTH_IDX + 1];
			int totalLength = 6 + dataSize;

			if (buffer.size() < totalLength)
				hasDataToParse = false;
			else
			{
				std::vector<unsigned char> extractedData;
				for (int i = 0; i < totalLength; i++)
				{
					extractedData.push_back(buffer.front());
					buffer.erase(buffer.begin());
				}

				int transactionId = (extractedData[0] << 8) | extractedData[1];
				int protocolId = (extractedData[2] << 8) | extractedData[3];
				int unitIdentifier = extractedData[UNIT_IDENTIFIER_IDX];
				int functionCode = extractedData[FUNCTION_IDX];

				switch (functionCode)
				{
				// Holding registers :
				case 0x03:
					if (extractedData.size() >= 12)
					{
						int startAddress = (extractedData[8] << 8) | extractedData[9];
						int nbWord = (extractedData[10] << 8) | extractedData[11];
						operations.Add(new ModbusReadMultipleWord(client, transactionId, protocolId, unitIdentifier, startAddress, nbWord));
					}
					break;

				case 0x06:
					if (extractedData.size() >= 12)
					{
						int wordAddress = (extractedData[8] << 8) | extractedData[9];
						int wordValue = (extractedData[10] << 8) | extractedData[11];
						operations.Add(new ModbusWriteWord(client, transactionId, protocolId, unitIdentifier, wordAddress, wordValue));
					}
					break;

				// Coils :
				case 0x01:
					if (extractedData.size() >= 12)
					{
						int startAddress = (extractedData[8] << 8) | extractedData[9];
						int nbCoil = (extractedData[10] << 8) | extractedData[11];
						operations.Add(new ModbusReadCoils(client, transactionId, protocolId, unitIdentifier, startAddress, nbCoil));
					}
					break;

				case 0x05:
					if (extractedData.size() >= 12)
					{
						int coilAddress = (extractedData[8] << 8) | extractedData[9];
						int coilValue = (extractedData[10] << 8) | extractedData[11];

						bool bValue = true;
						if (coilValue == 0)
							bValue = false;

						operations.Add(new ModbusForceSingleCoil(client, transactionId, protocolId, unitIdentifier, coilAddress, coilValue));
					}
					break;

				// Digital inputs :
				case 0x02:
					if (extractedData.size() >= 12)
					{
						int startAddress = (extractedData[8] << 8) | extractedData[9];
						int nbInput = (extractedData[10] << 8) | extractedData[11];
						operations.Add(new ModbusReadDigitalInputs(client, transactionId, protocolId, unitIdentifier, startAddress, nbInput));
					}
					break;

				default:

					break;
				}
			}
		}
		else
			hasDataToParse = false;
	}
	
}

void ModbusParser::parse(SOCKET sock, unsigned char * buf, int length)
{
	Parser<ClientState>::parse(sock, buf, length);
}

ThreadSafeQueue<ModbusOperation *> & ModbusParser::getOperation()
{
	return operations;
}