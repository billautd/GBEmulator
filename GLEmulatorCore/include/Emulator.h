#pragma once

#include "Common.h"

class CORE_API Emulator
{
private:
	void init();
	void destroy();
public:
	Emulator();
	~Emulator();

	void runEmulator();
};

