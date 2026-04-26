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
	SDL_Window *window;
	SDL_Renderer *renderer;

	Cartridge loadedCartridge;
	Registers registers;
	CPU currentCPU;
	PPU currentPPU;

	std::vector<u8> memory = {};

public:
	Context();
	~Context();

	void init();
	void destroy();

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
