#include "ModbusVariableSimulation.h"



ModbusVariableSimulation::ModbusVariableSimulation()
{
}


ModbusVariableSimulation::~ModbusVariableSimulation()
{
}

// Coils:
bool ModbusVariableSimulation::readCoilValue(int coilAddress)
{
	bool bWordCreated = false;
	if (coilsMemory.find(coilAddress) == coilsMemory.end())
		bWordCreated = true;

	int result = coilsMemory[coilAddress];

	if (bWordCreated)
		notifyValueChange();

	return result;
}

bool ModbusVariableSimulation::writeCoilValue(int coilAddress, bool value)
{
	coilsMemory[coilAddress] = value;
	notifyValueChange();
	return true;
}

// Inputs :
bool ModbusVariableSimulation::readBinaryInputValue(int inputAddress)
{
	bool bWordCreated = false;
	if (binaryInputsMemory.find(inputAddress) == binaryInputsMemory.end())
		bWordCreated = true;

	int result = binaryInputsMemory[inputAddress];

	if (bWordCreated)
		notifyValueChange();

	return result;
}

bool ModbusVariableSimulation::simulateBinaryInputValue(int inputAddress, bool value)
{
	binaryInputsMemory[inputAddress] = value;
	notifyValueChange();
	return true;
}

// Holding registers :
int ModbusVariableSimulation::readHoldingRegisterValue(int wordAddress)
{
	bool bWordCreated = false;
	if (holdingRegistersmemory.find(wordAddress) == holdingRegistersmemory.end())
		bWordCreated = true;

	int result = holdingRegistersmemory[wordAddress];

	if (bWordCreated)
		notifyValueChange();

	return result;
}

bool ModbusVariableSimulation::writeHoldingRegisterValue(int wordAddress, int value)
{
	holdingRegistersmemory[wordAddress] = value;
	notifyValueChange();
	return true;
}

void ModbusVariableSimulation::notifyValueChange()
{
	for (int i = 0; i < this->eventListeners.size(); i++)
	{
		eventListeners[i]->valueChanged(this);
	}
}