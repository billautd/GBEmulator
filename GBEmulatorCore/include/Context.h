#pragma once

#include <Common.h>
#include <Cartridge.h>
#include <Registers.h>
#include <CPU.h>
#include <PPU.h>

const static int TICKS_PER_FRAME = 70224;

class CORE_API Context
{
private:
	bool running = false;
	SDL_Window *window;
	SDL_Renderer *renderer;

	u64 tCycles;

	Cartridge loadedCartridge;
	Registers registers;
	CPU currentCPU;
	PPU currentPPU;

	// 0x0000	0x3FFF	16 KiB ROM bank 00 -> From cartridge, usually a fixed bank
	// 0x4000	0x7FFF	16 KiB ROM Bank 01–NN -> From cartridge, switchable bank via mapper (if any)
	// 0x8000	0x9FFF	8 KiB Video RAM (VRAM) -> In CGB mode, switchable bank 0/1
	// 0xA000	0xBFFF	8 KiB External RAM -> From cartridge, switchable bank if any
	// 0xC000	0xCFFF	4 KiB Work RAM (WRAM)
	// 0xD000	0xDFFF	4 KiB Work RAM (WRAM) -> In CGB mode, switchable bank 1–7
	// 0xE000	0xFDFF	Echo RAM (mirror of C000–DDFF) -> Nintendo says use of this area is prohibited.
	// 0xFE00	0xFE9F	Object attribute memory (OAM)
	// 0xFEA0	0xFEFF	Not Usable -> Nintendo says use of this area is prohibited.
	// 0xFF00	0xFF7F	I/O Registers
	// 0xFF80	0xFFFE	High RAM (HRAM)
	// 0xFFFF	0xFFFF	Interrupt Enable register (IE)

	//  I/O Ranges
	// $FF00			Joypad input
	// $FF01	$FF02	Serial transfer
	// $FF04	$FF07	Timer and divider
	// $FF0F			Interrupts
	// $FF10	$FF26	Audio
	// $FF30	$FF3F	Wave pattern
	// $FF40	$FF4B	LCD Control, Status, Position, Scrolling, and Palettes
	// $FF46			OAM DMA transfer
	// $FF4C	$FF4D	KEY0 and KEY1
	// $FF4F			VRAM Bank Select
	// $FF50			Boot ROM mapping control
	// $FF51	$FF55	VRAM DMA
	// $FF56			IR port
	// $FF68	$FF6B	BG / OBJ Palettes
	// $FF6C			Object priority mode
	// $FF70			WRAM Bank Select
	std::vector<u8> memory = {};

public:
	Context();
	~Context();

	void init();
	void destroy();

	u64 getTCycles() { return tCycles; }
	void setTCycles(u64 tCycles) { this->tCycles = tCycles; }
	void incTCycles(u64 inc) { this->tCycles += inc; }

	bool isRunning() { return running; }
	void setRunning(bool running) { this->running = running; }

	SDL_Window *getWindow() { return window; }
	SDL_Renderer *getRenderer() { return renderer; }

	Cartridge &getLoadedCartridge() { return loadedCartridge; }
	void loadCartridge(const char *path);

	Registers &regs() { return registers; }
	CPU &cpu() { return currentCPU; }
	PPU &ppu() { return currentPPU; }

	std::vector<u8> &mem() { return memory; }
	void initMemory();
	void logMemory();
};
