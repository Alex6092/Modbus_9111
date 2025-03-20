#include "PCI9111.h"


#include <Windows.h>
#include "Include/Dask64.h"

bool PCI9111::isCardValid()
{
	return cardID >= 0;
}

PCI9111::PCI9111()
{
	cardID = Register_Card(PCI_9111DG, 0);
}

PCI9111::~PCI9111()
{
	if (isCardValid())
	{
		Release_Card(cardID);
		cardID = -1;
	}
}

F64 PCI9111::ReadInput(U16 channel)
{
	if (isCardValid())
	{
		F64 tension;
		AI_VReadChannel(cardID, channel, AD_B_10_V, &tension);
		return tension;
	}
	
	return -1;
}
