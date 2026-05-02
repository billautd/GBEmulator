#include <Emulator.h>

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Usage : Path to ROM" << std::endl;
		return -1;
	}
	const char *romPath = argv[1];
	Emulator emulator;
	emulator.runEmulator(romPath);
	return 0;
}