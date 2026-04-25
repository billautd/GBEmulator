#pragma once

#include <Common.h>
#include <Cartridge.h>
#include <Registers.h>
#include <CPU.h>
#include <PPU.h>

class CORE_API Context
{
private:
	bool running = false;
	Cartridge loadedCartridge;
	Registers registers;
	CPU currentCPU;
	PPU currentPPU;

	std::vector<u8> memory = {};

public:
	Context();
	~Context();

	void init();

	bool isRunning() { return running; }
	void setRunning(bool running) { this->running = running; }

	Registers &regs() { return registers; }

	void loadCartridge(const char *path);
	Cartridge &getLoadedCartridge() { return loadedCartridge; }

	std::vector<u8> &mem() { return memory; }
	void initMemory();
	void logMemory();

	CPU &cpu() { return currentCPU; }

	PPU &ppu() { return currentPPU; }
};
