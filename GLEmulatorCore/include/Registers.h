#pragma once

#include "Common.h"

enum class R8 {	B, C, D, E, H, L, HL, A };
const std::string R8_STR[]{ "B", "C", "D", "E", "H", "L", "HL", "A" };

enum class R16{BC, DE, HL, SP};
const std::string R16_STR[]{ "BC", "DE", "HL", "SP" };

enum class R16_MEM { BC, DE, HLD, HLI };
const std::string R16_MEM_STR[]{ "BC", "DE", "HL-", "HL+" };

class CORE_API Registers
{
private:
public:
	//Accumulator
	u8 a = 0x00;
	u8 b = 0x00;
	u8 c = 0x00;
	u8 d = 0x00;
	u8 e = 0x00;
	//Flags
	u8 f = 0x00;
	u8 g = 0x00;
	u8 h = 0x00;
	u8 l = 0x00;
	//Program Counter
	u16 pc = 0x0000;
	//Stack Pointer
	u16 sp = 0x0000;

	void log();

	//From 3 bits data, get R8 to set
	static R8 getR8FromCode(u8 code);
	//Set u8 value in 8-bit register
	void setRegFromR8(R8 reg, u8 value);
	//Get 8-bit register value from R8
	u8 getFromR8(R8 reg);

	//From 2 bits data, get R16 to set
	static R16 getR16FromCode(u8 code);
	//Set u16 value in 2 8-bit registers
	void setRegFromR16(R16 reg, u16 value);

	//From 2 bits data, get R16_MEM to set
	static R16_MEM getR16MemFromCode(u8 code);
	//Gets byte pointed to by 2 8-bit registers
	u16 getPointerFromR16Mem(R16_MEM regMem);

	//Returns 1 byte after PC
	u8 imm8();
	//Returns 2 bytes after PC, in little endian order
	u16 imm16();
	//Returns address in HL
	void updateHLMem(R16_MEM r16Mem);

	//Set/reset all flags
	// 1 = SET
	// 0 = RESET
	// OTHER = UNCHANGED
	void setFlags(u8 z, u8 n, u8 h, u8 c);

	void setZFlag() { f |= 0b10000000; }
	void setNFlag() { f |= 0b01000000; }
	void setHFlag() { f |= 0b00100000; }
	void setCFlag() { f |= 0b00010000; }

	void resetZFlag() { f &= 0b01111111; }
	void resetNFlag() { f &= 0b10111111; }
	void resetHFlag() { f &= 0b11011111; }
	void resetCFlag() { f &= 0b11101111; }
};

