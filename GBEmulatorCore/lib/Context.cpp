#include <Context.h>
#include <sstream>

Context::Context() : currentCartridge(Cartridge(*this)), currentRegisters(Registers(*this)), currentCPU(CPU(*this)),
					 currentPPU(PPU(*this)), currentUI(UI(*this)), currentMemory(EmulatorMem(*this)), currentJoypad(Joypad(*this)),
					 currentDMA(DMA(*this)), currentTimer(Timer(*this))
{
	mem().init();
}

Context::~Context()
{
}

void Context::init(const char *romPath)
{
	tCycles = 0;

	cartridge().init(romPath);
	regs().init();
	ppu().init();
	timer().init();
}

void Context::destroy()
{
	mem().destroy();
	setRunning(false);
	currentUI.destroy();
}

std::stringstream oss;
void Context::tick(u64 inc)
{
	for (u64 i = 0; i < inc; i++)
	{
		tCycles++;
		cpu().tick();
		ppu().tick();
		joypad().tick();
		dma().tick();
		timer().tick();

		if (mem().readMem(0xFF02) == 0x81)
		{
			oss << mem().readMem(0xFF01);
			std::cout << oss.str();
			std::cerr << oss.str();
			mem().writeMem(0xFF02, 0);
		}
	}
}