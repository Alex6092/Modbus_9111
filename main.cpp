#include <conio.h>
#include <iostream>

#include "Modbus9111Sim.h"
#include "TcpServer.h"
#include "ModbusParser.h"
#include "ClientState.h"
#include "ModbusOperation.h"

int main(int argc, char ** argv)
{
	try
	{
		ModbusVariableSimulation* simulation = new Modbus9111Sim();
		TcpServer<ModbusParser, ClientState>* server = new TcpServer<ModbusParser, ClientState>(502);
		ModbusParser* parser = server->getParser();
		
		std::cout << "Server started & listening on port 502" << std::endl;

		while (1)
		{
			ThreadSafeQueue<ModbusOperation*> & operations = parser->getOperation();
			if (operations.Size() > 0)
			{
				std::cout << "Operation received" << std::endl;
				ModbusOperation* operation = operations.Get();
				if (operation != nullptr)
				{
					operation->Execute(simulation);
				}
			}

			Sleep(1);
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "End of execution, press any key to exit..." << std::endl;
	_getch();

	return 0;
}