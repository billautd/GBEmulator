#pragma once

#include "Common.h"
#include "Cartridge.h"
#include "Registers.h"
#include "CPU.h"

class CORE_API Context
{
private:
	bool running = false;
	Cartridge loadedCartridge;
	Registers registers;
	CPU currentCPU;

	u8 currentOpCode;

	std::vector<u8> memory = {};

public:
	Context();
	~Context();

	void init();

	bool isRunning() { return running; }
	void setRunning(bool running) { this->running = running; }

	Registers &regs() { return registers; }

	u8 opCode() { return currentOpCode; }
	void setCurrentOpCode(u8 opCode) { currentOpCode = opCode; }

	void loadCartridge(const char *path);
	Cartridge &getLoadedCartridge() { return loadedCartridge; }

	std::vector<u8> &mem() { return memory; }
	void initMemory();

	CPU &cpu() { return currentCPU; }
};
