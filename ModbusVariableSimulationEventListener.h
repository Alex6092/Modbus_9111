#pragma once

class ModbusVariableSimulation;

class ModbusVariableSimulationEventListener
{
public:
	ModbusVariableSimulationEventListener();
	~ModbusVariableSimulationEventListener();

	virtual void valueChanged(ModbusVariableSimulation * simulation) {}
};

