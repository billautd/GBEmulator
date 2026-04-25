#include <Context.h>

Context::Context() : loadedCartridge(Cartridge(*this)), registers(Registers(*this)), currentCPU(CPU(*this))
{
	init();
}

Context::~Context()
{
}

void Context::init()
{
	initMemory();
	registers.pc = 0x100;
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