#pragma once

#include <Common.h>
#include <Cartridge.h>
#include <Mem.h>
#include <Registers.h>
#include <CPU.h>
#include <PPU.h>
#include <UI.h>

class CORE_API Context
{
private:
	bool running = false;
	u64 tCycles;

	Cartridge loadedCartridge;
	Registers registers;
	Mem currentMemory;
	CPU currentCPU;
	PPU currentPPU;
	UI currentUI;

public:
	Context();
	~Context();

	void init();
	void destroy();

	u64 getTCycles() { return tCycles; }
	void tick(u64 inc);

	bool isRunning() { return running; }
	void setRunning(bool running) { this->running = running; }

	Cartridge &getLoadedCartridge() { return loadedCartridge; }
	void loadCartridge(const char *path);

	Registers &regs() { return registers; }
	CPU &cpu() { return currentCPU; }
	PPU &ppu() { return currentPPU; }
	UI &ui() { return currentUI; }
	Mem &mem() { return currentMemory; }

	void initMemory();
};
