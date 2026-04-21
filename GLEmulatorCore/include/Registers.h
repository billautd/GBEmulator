#pragma once

#include "Common.h"

enum class R8{UNKNOWN, B, C, D, E, H, L, HL, A};
const std::string R8_STR[]{ "UNKOWN", "B", "C", "D", "E", "H", "L", "HL", "A" };

enum class R16{UNKNOWN, BC, DE, HL, SP};
const std::string R16_STR[]{ "UNKOWN", "BC", "DE", "HL", "SP" };

enum class R16_MEM { UNKNOWN, BC, DE, HLD, HLI };
const std::string R16_MEM_STR[]{ "UNKOWN", "BC", "DE", "HL-", "HL+" };

class CORE_API Registers
{
private:
public:
	//Accumulator
	u8 a;
	u8 b;
	u8 c;
	u8 d;
	u8 e;
	//Flags
	u8 f;
	u8 g;
	u8 h;
	u8 l;
	//Program Counter
	u16 pc;
	//Stack Pointer
	u16 sp;

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

	void setZFlag() { f |= 0x10000000; }
	void setNFlag() { f |= 0x01000000; }
	void setHFlag() { f |= 0x00100000; }
	void setCFlag() { f |= 0x00010000; }

	void resetZFlag() { f &= 0x01111111; }
	void resetNFlag() { f &= 0x10111111; }
	void resetHFlag() { f &= 0x11011111; }
	void resetCFlag() { f &= 0x11101111; }
};

