#include <Registers.h>
#include <Context.h>

Registers::Registers(Context &ctx) : ctx(ctx)
{
}

Registers::~Registers()
{
}

void Registers::log()
{
	std::cout << "A[" << Common::toHexStr(a)
			  << "], B[" << Common::toHexStr(b)
			  << "], C[" << Common::toHexStr(c)
			  << "], D[" << Common::toHexStr(d)
			  << "], E[" << Common::toHexStr(e)
			  << "], F[" << Common::toHexStr(f)
			  << "], G[" << Common::toHexStr(g)
			  << "], H[" << Common::toHexStr(h)
			  << "], L[" << Common::toHexStr(l)
			  << "], PC[" << Common::toHexStr(pc)
			  << "], SP[" << Common::toHexStr(sp)
			  << "]" << std::endl;
}

R8 Registers::getR8FromCode(u8 data)
{
	switch (data)
	{
	case 0:
		return R8::B;
	case 1:
		return R8::C;
	case 2:
		return R8::D;
	case 3:
		return R8::E;
	case 4:
		return R8::H;
	case 5:
		return R8::L;
	case 6:
		return R8::HL;
	case 7:
		return R8::A;
	}
	throw std::invalid_argument(std::string("Registers::getR8FromCode -> Invalid R8 code " + data));
}

void Registers::setRegFromR8(R8 reg, u8 value)
{
	switch (reg)
	{
	case R8::B:
	{
		b = value;
		break;
	}
	case R8::C:
	{
		c = value;
		break;
	}
	case R8::D:
	{
		d = value;
		break;
	}
	case R8::E:
	{
		e = value;
		break;
	}
	case R8::H:
	{
		h = value;
		break;
	}
	case R8::L:
	{
		l = value;
		break;
	}
	case R8::A:
	{
		a = value;
		break;
	}
	case R8::HL:
	{
		ctx.mem().at(hl()) = value;
		break;
	}
	default:
		throw std::invalid_argument(std::string("Registers::setRegFromR8 -> Invalid R8 reg " + R8_STR[(int)reg]));
	}
}

u8 Registers::getFromR8(R8 reg)
{
	switch (reg)
	{
	case R8::B:
		return b;
	case R8::C:
		return c;
	case R8::D:
		return d;
	case R8::E:
		return e;
	case R8::H:
		return h;
	case R8::L:
		return l;
	case R8::A:
		return a;
	case R8::HL:
	{
		// TODO
	}
	}
	throw std::invalid_argument(std::string("Registers::getFromR8 -> Invalid R8 reg " + R8_STR[(int)reg]));
}

R16 Registers::getR16FromCode(u8 data)
{
	switch (data)
	{
	case 0:
		return R16::BC;
	case 1:
		return R16::DE;
	case 2:
		return R16::HL;
	case 3:
		return R16::SP;
	}
	throw std::invalid_argument(std::string("Registers::getR16FromCode -> Invalid R16 code " + data));
}

void Registers::setRegFromR16(R16 reg, u16 value)
{
	u8 first = value >> 8;
	u8 second = value & 0xFF;

	switch (reg)
	{
	case R16::BC:
	{
		b = first;
		c = second;
		break;
	}
	case R16::DE:
	{
		d = first;
		e = second;
		break;
	}
	case R16::HL:
	{
		h = first;
		l = second;
		break;
	}
	case R16::SP:
	{
		sp = value;
		break;
	}
	default:
		throw std::invalid_argument(std::string("Registers::setRegFromR16 -> Invalid R16 reg " + R16_STR[(int)reg]));
	}
}

R16_MEM Registers::getR16MemFromCode(u8 data)
{
	switch (data)
	{
	case 0:
		return R16_MEM::BC;
	case 1:
		return R16_MEM::DE;
	case 2:
		return R16_MEM::HLI;
	case 3:
		return R16_MEM::HLD;
	}
	throw std::invalid_argument(std::string("Registers::getR16MemFromCode -> Invalid R16 mem code " + data));
}

u16 Registers::getPointerFromR16Mem(R16_MEM regMem)
{
	switch (regMem)
	{
	case R16_MEM::BC:
	{
		return b * 256 + c;
	}
	case R16_MEM::DE:
	{
		return d * 256 + e;
	}
	case R16_MEM::HLI:
	case R16_MEM::HLD:
	{
		return h * 256 + l;
	}
	}
	throw std::invalid_argument(std::string("Registers::getPointerFromR16Mem -> Invalid R16 mem reg " + R16_MEM_STR[(int)regMem]));
}

u8 Registers::imm8()
{
	return ctx.mem().at(pc + 1);
}

u16 Registers::imm16()
{
	u8 bigValue = ctx.mem().at(pc + 2);
	u8 littleValue = ctx.mem().at(pc + 1);
	return bigValue * 256 + littleValue;
}

u16 Registers::hl()
{
	return h * 256 + l;
}

void Registers::updateHLMem(R16_MEM r16Mem)
{
	// If using HLI, value in HL should be incremented. We get value present in HL and set it back as itself + 1
	if (r16Mem == R16_MEM::HLI)
	{
		setRegFromR16(R16::HL, getPointerFromR16Mem(r16Mem) + 1);
		std::cout << "Incremented HL to " << Common::toHexStr(l) << Common::toHexStr(h) << std::endl;
	}
	// If using HLD, value in HL should be decremented. We get value present in HL and set it back as itself - 1
	else if (r16Mem == R16_MEM::HLD)
	{
		setRegFromR16(R16::HL, getPointerFromR16Mem(r16Mem) - 1);
		std::cout << "Decrement HL to " << Common::toHexStr(l) << Common::toHexStr(h) << std::endl;
	}
}

void Registers::setFlags(u8 z, u8 n, u8 h, u8 c)
{
	if (z == 1)
		setZFlag();
	else if (z == 0)
		resetZFlag();

	if (n == 1)
		setNFlag();
	else if (n == 0)
		resetNFlag();

	if (h == 1)
		setHFlag();
	else if (h == 0)
		resetHFlag();

	if (c == 1)
		setCFlag();
	else if (c == 0)
		resetCFlag();
}