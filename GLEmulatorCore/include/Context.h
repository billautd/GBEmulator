#pragma once

#include "Common.h"
#include "Cartridge.h"
#include "Registers.h"

class CORE_API Context
{
private:
	bool running = false;
	Cartridge loadedCartridge;
	Registers registers;

	u8 currentOpCode;

	static Context* INSTANCE;

	std::vector<u8> memory = {};
public:
	static Context* get() {
		if (INSTANCE == nullptr) {
			std::cout << "Initializing context" << std::endl;
			INSTANCE = new Context();
		}
		return INSTANCE;
	}

	Context();
	~Context();

	bool isRunning() { return running; }
	void setRunning(bool running) {	this->running = running; }

	Registers& getRegisters() { return registers; }

	u8 getCurrentOpCode() { return currentOpCode; }
	void setCurrentOpCode(u8 opCode) { currentOpCode = opCode; }

	void loadCartridge(const char* path);
	Cartridge& getLoadedCartridge() { return loadedCartridge; }

	std::vector<u8>& getMemory() { return memory; }
	void initMemory();
};

