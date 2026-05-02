#include <Emulator.h>
#include <CPU.h>
#include <SDL3_ttf/SDL_ttf.h>

const static int CYCLES_PER_FRAME = 70224;
const static float NS_PER_SEC = 1'000'000'000;
const static float SEC_PER_FRAME = (float)CYCLES_PER_FRAME / 4'194'304;
const static float NS_PER_FRAME = SEC_PER_FRAME * NS_PER_SEC;

Emulator::Emulator() : ctx(Context())
{
}

Emulator::~Emulator()
{
}

void Emulator::init()
{
	ctx.init();
	ctx.setRunning(true);
	ctx.ui().init();
	return;
}

void Emulator::runEmulator(const char *romPath)
{
	init();
	ctx.loadCartridge(romPath);

	u64 nextTCyclesTarget = CYCLES_PER_FRAME;
	while (ctx.isRunning())
	{
		u64 previousFrame = ctx.ppu().getFrame();
		/*****************/
		/*****MAIN LOOP***/
		/*****************/
		// Timing to the nanosecond, wait for full frame
		u64 ticksStart = Common::getTicks();
		while (ctx.getTCycles() < nextTCyclesTarget)
		{
			ctx.tick(1);
		}
		u64 elapsedTime = Common::getTicks() - ticksStart;
		u64 remaining = NS_PER_FRAME - elapsedTime;
		if (remaining > 0)
			Common::delay(remaining);
		// Update next frame target
		nextTCyclesTarget += CYCLES_PER_FRAME;

		// Render UI
		if (ctx.ppu().getFrame() != previousFrame)
		{
			ctx.ui().handle();
			ctx.ui().update();
			ctx.ui().setFPS((float)1'000'000'000 / (Common::getTicks() - ticksStart));
		}
	}
	destroy();
	return;
}

void Emulator::destroy()
{
	std::cout << "Exiting" << std::endl;
	ctx.destroy();
	SDL_Quit();
}
