#pragma once

#include <Cartridge.h>
#include <Common.h>
#include <CPU.h>
#include <DMA.h>
#include <EmulatorMem.h>
#include <Joypad.h>
#include <PPU.h>
#include <Registers.h>
#include <Timer.h>
#include <UI.h>

class CORE_API Context
{
private:
	bool running = false;
	u64 tCycles;

	Cartridge currentCartridge;
	CPU currentCPU;
	DMA currentDMA;
	Joypad currentJoypad;
	EmulatorMem currentMemory;
	PPU currentPPU;
	Registers currentRegisters;
	Timer currentTimer;
	UI currentUI;

public:
	Context();
	~Context();

	void init(const char *romPath);
	void destroy();

	u64 getTCycles() { return tCycles; }
	void tick(u64 inc);

	bool isRunning() { return running; }
	void setRunning(bool running) { this->running = running; }

	Cartridge &cartridge() { return currentCartridge; }
	CPU &cpu() { return currentCPU; }
	DMA &dma() { return currentDMA; }
	EmulatorMem &mem() { return currentMemory; }
	Joypad &joypad() { return currentJoypad; }
	PPU &ppu() { return currentPPU; }
	Registers &regs() { return currentRegisters; }
	Timer &timer() { return currentTimer; }
	UI &ui() { return currentUI; }
};
