#include "../include/Context.h"

Context* Context::INSTANCE = nullptr;

Context::Context():currentOpCode(-1), loadedCartridge(Cartridge()), registers(Registers()) {
	initMemory();
	registers.pc = 0x100;
}

void Context::loadCartridge(const char* path)
{
	loadedCartridge.loadCartrige(path);
}

void Context::initMemory() {
	memory = {};
	memory.resize(0x10000);
}