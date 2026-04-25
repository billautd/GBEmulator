#pragma once

#include <Common.h>
#include <Context.h>

class CORE_API Emulator
{
private:
	Context ctx;
	SDL_Window *window;

	void init();
	void destroy();

public:
	Emulator();
	~Emulator();

	void runEmulator();

	Context &getContext() { return ctx; }
};
