#include <Emulator.h>
#include <CPU.h>
#include <SDL3_ttf/SDL_ttf.h>

const static i64 CYCLES_PER_FRAME = 70224;
const static i64 NS_PER_FRAME = 16'742'706;

void Emulator::runEmulator(const char *romPath)
{
	init(romPath);

	u64 nextTCyclesTarget = CYCLES_PER_FRAME;
	while (ctx.isRunning())
	{
		/*****************/
		/*****MAIN LOOP***/
		/*****************/
		// Timing to the nanosecond, wait for full frame
		u64 ticksStart = Common::getTicks();
		while (ctx.getTCycles() < nextTCyclesTarget)
			try
			{
				ctx.tick(1);
			}
			catch (std::runtime_error e)
			{
				std::cerr << e.what() << std::endl;
				ctx.setRunning(false);
			}

		// Update next frame target
		nextTCyclesTarget += CYCLES_PER_FRAME;

		// Render UI
		ctx.ui().handle();
		ctx.ui().update();

		i64 remaining = NS_PER_FRAME - (i64)(Common::getTicks() - ticksStart);
		// Sleep for most part of loop but not the last 2 ms
		if (remaining > 2'000'000)
			Common::delay(remaining - 2'000'000);
		// Busy wait for last 2 ms
		while (NS_PER_FRAME - (i64)(Common::getTicks() - ticksStart) > 0)
			;

		ctx.ui().setFPS(1'000'000'000.0f / (Common::getTicks() - ticksStart));
		if (ctx.ppu().getFrame() % 120 == 0)
			std::cout << "FPS : " << ctx.ui().getFPS() << std::endl;

		FrameMark;
	}
	destroy();
	return;
}

Emulator::Emulator() : ctx(Context())
{
}

Emulator::~Emulator()
{
}

void Emulator::init(const char *romPath)
{
	ctx.init(romPath);
	ctx.setRunning(true);
	ctx.ui().init();
	return;
}

void Emulator::destroy()
{
	std::cout << "Exiting" << std::endl;
	ctx.destroy();
	SDL_Quit();
}
