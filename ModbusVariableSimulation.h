#pragma once

#include <map>
#include <vector>
#include <algorithm>
#include "ModbusVariableSimulationEventListener.h"

class ModbusVariableSimulation
{
	std::map<int, bool> coilsMemory;
	std::map<int, bool> binaryInputsMemory;
	std::map<int, int> holdingRegistersmemory;
	std::vector<ModbusVariableSimulationEventListener *> eventListeners;


	void notifyValueChange();
public:
	ModbusVariableSimulation();
	~ModbusVariableSimulation();

	// Coils:
	virtual bool readCoilValue(int coilAddress);
	virtual bool writeCoilValue(int coilAddress, bool value);

	// Inputs :
	virtual bool readBinaryInputValue(int inputAddress);
	virtual bool simulateBinaryInputValue(int inputAddress, bool value);

	// Holding registers :
	virtual int readHoldingRegisterValue(int wordAddress);
	virtual bool writeHoldingRegisterValue(int wordAddress, int value);

	inline const std::map<int, int> & getHoldingRegistersMemory() { return holdingRegistersmemory; }

	inline const std::map<int, bool> & getCoilsMemory() { return coilsMemory; }

	inline const std::map<int, bool> & getBinaryInputsMemory() { return binaryInputsMemory; }

	inline void addEventListener(ModbusVariableSimulationEventListener * listener)
	{
		eventListeners.push_back(listener);
	}

	inline void removeEventListener(ModbusVariableSimulationEventListener * listener)
	{
		auto it = std::find(eventListeners.begin(), eventListeners.end(), listener);
		if (it != eventListeners.end())
		{
			eventListeners.erase(it);
		}
	}
};

