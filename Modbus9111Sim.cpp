#include "Modbus9111Sim.h"

int Modbus9111Sim::readHoldingRegisterValue(int wordAddress)
{
	if (wordAddress >= 0 && wordAddress < 16 && carte.isCardValid())
	{
		double tension = carte.ReadInput(wordAddress);
		int result = -1;
		if (result >= 0)
		{
			result = (int)((tension / 10.0) * 65535);
		}
		return result;
	}
    return 0;
}
