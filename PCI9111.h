#pragma once

class PCI9111
{
	short cardID;

public:
	PCI9111();
	~PCI9111();
	bool isCardValid();
	double ReadInput(unsigned short channel);
};

