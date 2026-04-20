#include "../include/Emulator.h"
#include "../include/Context.h"

Emulator::Emulator() {

}

Emulator::~Emulator() {
	destroy();
}

void Emulator::init() {
	SDL_Init(SDL_INIT_VIDEO);
	Context::get()->setRunning(true);
	return;
}

void Emulator::runEmulator()
{
	init();
	Context::get()->loadCartridge("../../t.gb");
	Context::get()->getRegisters().pc = 0x100;

	while (Context::get()->isRunning()) {
		Common::delay(100);
		Operations::runOp();
	}
	return;
}

void Emulator::destroy() {

}
