#pragma once

#include <Common.h>

// 0x0000	0x3FFF	16 KiB ROM bank 00 -> From cartridge, usually a fixed bank
// 0x4000	0x7FFF	16 KiB ROM Bank 01–NN -> From cartridge, switchable bank via mapper (if any)
// 0x8000	0x9FFF	8 KiB Video RAM (VRAM) -> In CGB mode, switchable bank 0/1
// 0xA000	0xBFFF	8 KiB External RAM -> From cartridge, switchable bank if any
// 0xC000	0xCFFF	4 KiB Work RAM (WRAM)
// 0xD000	0xDFFF	4 KiB Work RAM (WRAM) -> In CGB mode, switchable bank 1–7
// 0xE000	0xFDFF	Echo RAM (mirror of C000–DDFF) -> Nintendo says use of this area is prohibited.
// 0xFE00	0xFE9F	Object attribute memory (OAM)
// 0xFEA0	0xFEFF	Not Usable -> Nintendo says use of this area is prohibited.
// 0xFF00	0xFF7F	I/O Registers
// 0xFF80	0xFFFE	High RAM (HRAM)
// 0xFFFF	0xFFFF	Interrupt Enable register (IE)

//  I/O Ranges
// $FF00			Joypad input
// $FF01	$FF02	Serial transfer
// $FF04	$FF07	Timer and divider
// $FF0F			Interrupts
// $FF10	$FF26	Audio
// $FF30	$FF3F	Wave pattern
// $FF40	$FF4B	LCD Control, Status, Position, Scrolling, and Palettes
// $FF46			OAM DMA transfer
// $FF4C	$FF4D	KEY0 and KEY1
// $FF4F			VRAM Bank Select
// $FF50			Boot ROM mapping control
// $FF51	$FF55	VRAM DMA
// $FF56			IR port
// $FF68	$FF6B	BG / OBJ Palettes
// $FF6C			Object priority mode
// $FF70			WRAM Bank Select
class Context;
class CORE_API EmulatorMem
{
private:
    Context &ctx;
    std::vector<u8> data = {};
public:
    EmulatorMem(Context &ctx);
    ~EmulatorMem();

    const static int MEM_SIZE = 0x10000;

    void init();
    void destroy();

    std::vector<u8> &getMem() { return data; }
    
    void logMem();
    // Writes value to memory, checks for PPU mode if address in VRAM
    void writeMem(u16 address, u8 value);
    // Reads value from memory, checks for PPU mode if address in VRAM
    u8 readMem(u16 address);
};