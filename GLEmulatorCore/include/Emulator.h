#pragma once

#include "Common.h"

class Emulator
{
private:
	void init();
	void destroy();
public:
	Emulator();
	~Emulator();

	void runEmulator();
};

