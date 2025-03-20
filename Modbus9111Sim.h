#pragma once
#include "ModbusVariableSimulation.h"
#include "PCI9111.h"
class Modbus9111Sim : public ModbusVariableSimulation
{
	PCI9111 carte;

public:
	virtual int readHoldingRegisterValue(int wordAddress);
};

