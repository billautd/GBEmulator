#include <Emulator.h>
#include <CPU.h>

Emulator::Emulator() : ctx(Context())
{
}

Emulator::~Emulator()
{
	destroy();
}

void Emulator::init()
{
	SDL_Init(SDL_INIT_VIDEO);
	ctx.setRunning(true);
	return;
}

void Emulator::runEmulator()
{
	init();
	ctx.loadCartridge("../../../t.gb");
	ctx.regs().pc = 0x100;

	while (ctx.isRunning())
	{
		Common::delay(100);
		// Unsupported operation
		try
		{
			ctx.cpu().runOp();
		}
		catch (std::runtime_error &e)
		{
			std::cerr << e.what() << std::endl;
			ctx.setRunning(false);
		}
	}
	return;
}

void Emulator::destroy()
{
}
