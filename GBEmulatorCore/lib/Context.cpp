#include <Context.h>

Context::Context() : loadedCartridge(Cartridge(*this)), registers(Registers(*this)), currentCPU(CPU(*this)),
					 currentPPU(PPU(*this)), currentUI(UI(*this)), currentMemory(Mem(*this)), currentJoypad(Joypad(*this))
{
	init();
}

Context::~Context()
{
}

void Context::init()
{
	tCycles = 0;

	mem().init();
	regs().init();
	ppu().init();
}

void Context::destroy()
{
	mem().destroy();
	setRunning(false);
	currentUI.destroy();
}

void Context::loadCartridge(const char *path)
{
	loadedCartridge.loadCartrige(path);
}

void Context::tick(u64 inc)
{
	// Ticks CPU and PPU individually since PPU instructions can be run in between CPU steps
	// Ticks T-Cycles, not M-Cycles so most instructions should be tick(4)
	for (u64 i = 0; i < inc; i++)
	{
		tCycles++;
		cpu().tick();
		ppu().tick();
		joypad().tick();
	}
}