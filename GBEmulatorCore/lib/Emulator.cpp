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
	window = SDL_CreateWindow("", 600, 400, 0);
	ctx.setRunning(true);
	return;
}

void Emulator::runEmulator()
{
	init();
	ctx.loadCartridge("../t.gb");

	SDL_Event evt;
	while (ctx.isRunning())
	{
		//  Unsupported operation
		try
		{
			ctx.cpu().runOp();
			ctx.ppu().run();
		}
		catch (std::runtime_error &e)
		{
			std::cerr << e.what() << std::endl;
			destroy();
		}

		// Listen to process exit
		while (SDL_PollEvent(&evt))
		{

			if (evt.type == SDL_EVENT_QUIT)
			{
				std::cout << "Exiting" << std::endl;
				destroy();
			}
		}
		SDL_Delay(10);
	}
	return;
}

void Emulator::destroy()
{
	ctx.setRunning(false);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
