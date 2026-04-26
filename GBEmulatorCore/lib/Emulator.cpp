#include <Emulator.h>
#include <CPU.h>
#include <SDL3_ttf/SDL_ttf.h>

const static int CYCLES_PER_FRAME = 70224;
const static float NS_PER_SEC = 1000000000;
const static float SEC_PER_FRAME = (float)CYCLES_PER_FRAME / 4194304;
const static float NS_PER_FRAME = SEC_PER_FRAME * NS_PER_SEC;

Emulator::Emulator() : ctx(Context())
{
}

Emulator::~Emulator()
{
	destroy();
}

void Emulator::init()
{
	ctx.init();
	ctx.setRunning(true);
	return;
}

void Emulator::runEmulator()
{
	init();
	ctx.loadCartridge("../t.gb");

	SDL_Event evt;

	u64 nextTCyclesTarget = CYCLES_PER_FRAME;
	while (ctx.isRunning())
	{
		/*****************/
		/*****MAIN LOOP***/
		/*****************/
		// Timing to the nanosecond, wait for full frame
		u64 ticksStart = Common::getTicks();
		while (ctx.getTCycles() < nextTCyclesTarget)
		{
			//  Unsupported operation
			try
			{
				u64 tCyclesStart = ctx.getTCycles();
				ctx.cpu().runOp();
				ctx.ppu().run(ctx.getTCycles() - tCyclesStart);
			}
			catch (std::runtime_error &e)
			{
				std::cerr << "Exception : " << e.what() << std::endl;
				destroy();
			}
		}
		u64 elapsedTime = Common::getTicks() - ticksStart;
		if (elapsedTime < NS_PER_FRAME)
			Common::delay(NS_PER_FRAME - elapsedTime);
		// Update next frame target
		nextTCyclesTarget += CYCLES_PER_FRAME;

		// Render UI
		ctx.ppu().displayTileMap();

		// Update FPS
		fps = (float)1000000000 / (Common::getTicks() - ticksStart);

		// Listen to process exit
		while (SDL_PollEvent(&evt))
		{
			if (evt.type == SDL_EVENT_QUIT)
			{
				std::cout << "Exiting" << std::endl;
				std::cout << ctx.getTCycles() << std::endl;
				destroy();
			}
		}
	}
	return;
}

void Emulator::destroy()
{
	ctx.destroy();
	SDL_Quit();
}
