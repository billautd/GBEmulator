#include <Context.h>
#include <fstream>
#include <SDL3_ttf/SDL_ttf.h>

Context::Context() : loadedCartridge(Cartridge(*this)), registers(Registers(*this)), currentCPU(CPU(*this)),
					 currentPPU(PPU(*this))
{
	init();
}

Context::~Context()
{
}

void Context::init()
{
	tCycles = 0;

	// Init memory
	initMemory();
	registers.pc = 0x100;
	memory.at(PPU::LY_ADDR) = 0;

	// Init window
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("GBEmulator", 1920, 1080, 0, &window, &renderer);

	// Init fonts
	TTF_Init();
}

void Context::destroy()
{
	logMemory();
	setRunning(false);
	SDL_DestroyWindow(window);
}

void Context::loadCartridge(const char *path)
{
	loadedCartridge.loadCartrige(path);
}

void Context::initMemory()
{
	memory = {};
	memory.resize(0x10000);
}

void Context::logMemory()
{
	std::ofstream logFile("memory.txt");
	logFile << regs().log() << std::endl
			<< std::endl;
	logFile << "      00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F" << std::endl;
	for (int i = 0; i < memory.size(); i++)
	{
		if ((i % 16) == 0)
		{
			logFile << Common::toHexStr((u16)(i / 16)) << "  ";
		}
		logFile << Common::toHexStr(memory.at(i)) << "  ";
		if ((i % 16) == 15)
		{
			logFile << std::endl;
		}
	}
}