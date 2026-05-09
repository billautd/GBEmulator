#pragma once

#include <Common.h>

enum class R8
{
	B,
	C,
	D,
	E,
	H,
	L,
	HL,
	A
};
const std::string R8_STR[]{"B", "C", "D", "E", "H", "L", "HL", "A"};

enum class R16
{
	BC,
	DE,
	HL,
	SP
};
const std::string R16_STR[]{"BC", "DE", "HL", "SP"};

enum class R16_MEM
{
	BC,
	DE,
	HLD,
	HLI
};
const std::string R16_MEM_STR[]{"BC", "DE", "HL-", "HL+"};

enum class R16_STK
{
	BC,
	DE,
	HL,
	AF
};
const std::string R16_STK_STR[]{"BC", "DE", "HL", "AF"};

enum class COND
{
	NZ,
	Z,
	NC,
	C
};
const std::string COND_STR[]{"NZ", "Z", "NC", "C"};

class Context;
class CORE_API Registers
{
private:
	Context &ctx;

public:
	Registers(Context &ctx);
	~Registers();

	// Accumulator
	u8 a = 0x00;
	u8 b = 0x00;
	u8 c = 0x00;
	u8 d = 0x00;
	u8 e = 0x00;
	// Flags : ZNHC 0000
	u8 f = 0x00;
	u8 h = 0x00;
	u8 l = 0x00;
	// Program Counter
	u16 pc = 0x0000;
	// Stack Pointer
	u16 sp = 0x0000;

	void init();
	std::string log();

	// From 3 bits data, get R8 to set
	static R8 getR8FromCode(u8 code);
	// Set u8 value in 8-bit register
	void setRegFromR8(R8 reg, u8 value);
	// Get 8-bit register value from R8
	u8 getFromR8(R8 reg);

	// From 2 bits data, get R16 to set
	static R16 getR16FromCode(u8 code);
	// Set u16 value in 2 8-bit registers
	void setRegFromR16(R16 reg, u16 value);
	// Get 16-bit register value from R16
	u16 getFromR16(R16 reg);

	// From 2 bits data, get R16_STK to set
	static R16_STK getR16StkFromCode(u8 code);
	// Set u16 value in 2 8-bit registers
	void setRegFromR16Stk(R16_STK reg, u16 value);
	// Get 16-bit register value from R16_STK
	u16 getFromR16Stk(R16_STK reg);

	// From 2 bits data, get R16_MEM to set
	static R16_MEM getR16MemFromCode(u8 code);
	// Gets byte pointed to by 2 8-bit registers
	u16 getPointerFromR16Mem(R16_MEM regMem);

	// From 2 bits data, get COND
	static COND getCONDFromCode(u8 code);
	// Checks condition of F register
	bool checkCOND(COND cond);

	// From 3 bits data, get TGT3
	static u16 getTGT3FromCode(u8 code);

	// Returns 1 byte after PC
	u8 imm8();
	// Returns 2 bytes after PC, in little endian order
	u16 imm16();
	// Increments or decrements HL dependening on R16_MEM HL+ or HL-
	void updateHLMem(R16_MEM r16Mem);

	// Set/reset all flags
	//  1 = SET
	//  0 = RESET
	//  OTHER = UNCHANGED
	void setFlags(u8 z, u8 n, u8 h, u8 c);

	bool getZFlag() { return Common::getBit(f, 7); }
	bool getNFlag() { return Common::getBit(f, 6); }
	bool getHFlag() { return Common::getBit(f, 5); }
	bool getCFlag() { return Common::getBit(f, 4); }

	void setZFlag() { f = Common::setBit(f, 7); }
	void setNFlag() { f = Common::setBit(f, 6); }
	void setHFlag() { f = Common::setBit(f, 5); }
	void setCFlag() { f = Common::setBit(f, 4); }

	void resetZFlag() { f = Common::resetBit(f, 7); }
	void resetNFlag() { f = Common::resetBit(f, 6); }
	void resetHFlag() { f = Common::resetBit(f, 5); }
	void resetCFlag() { f = Common::resetBit(f, 4); }
};
