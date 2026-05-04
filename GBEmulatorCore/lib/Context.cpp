#include <Context.h>

Context::Context() : currentCartridge(Cartridge(*this)), currentRegisters(Registers(*this)), currentCPU(CPU(*this)),
					 currentPPU(PPU(*this)), currentUI(UI(*this)), currentMemory(EmulatorMem(*this)), currentJoypad(Joypad(*this)),
					 currentDMA(DMA(*this))
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

void Context::tick(u64 inc)
{
	for (u64 i = 0; i < inc; i++)
	{
		tCycles++;
		cpu().tick();
		ppu().tick();
		joypad().tick();
		dma().tick();
	}
}