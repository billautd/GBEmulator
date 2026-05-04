#pragma once

#include <Common.h>
#include <Cartridge.h>
#include <EmulatorMem.h>
#include <Registers.h>
#include <CPU.h>
#include <DMA.h>
#include <PPU.h>
#include <UI.h>
#include <Joypad.h>

class CORE_API Context
{
private:
	bool running = false;
	u64 tCycles;

	Cartridge currentCartridge;
	Registers currentRegisters;
	EmulatorMem currentMemory;
	CPU currentCPU;
	PPU currentPPU;
	UI currentUI;
	Joypad currentJoypad;
	DMA currentDMA;

public:
	Context();
	~Context();

	void init();
	void destroy();

	u64 getTCycles() { return tCycles; }
	void tick(u64 inc);

	bool isRunning() { return running; }
	void setRunning(bool running) { this->running = running; }

	Cartridge &cartridge() { return currentCartridge; }
	Registers &regs() { return currentRegisters; }
	CPU &cpu() { return currentCPU; }
	PPU &ppu() { return currentPPU; }
	UI &ui() { return currentUI; }
	EmulatorMem &mem() { return currentMemory; }
	Joypad &joypad() { return currentJoypad; }
	DMA &dma() { return currentDMA; }
};
