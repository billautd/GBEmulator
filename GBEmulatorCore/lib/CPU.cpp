#include <CPU.h>
#include <Context.h>

CPU::CPU(Context &ctx) : ctx(ctx)
{
}

CPU::~CPU()
{
}

void CPU::runOp()
{
	u8 code = ctx.mem().at(ctx.regs().pc);
	ctx.setCurrentOpCode(code);
	std::cout << "Current op code : " << Common::toHexStr(code) << std::endl;
	ctx.regs().log();
	// Call main method with op code
	runOp(code);
}

void CPU::runOp(u8 code)
{
	// Block 0
	// 0x00
	if (code == 0)
	{
		std::cout << "nop" << std::endl;
		nop();
	}
	// 0x01 (BC), 0x11 (DE), 0x21 (HL), 0x31 (SP)
	else if ((code & 0b11001111) == 0b00000001)
	{
		std::cout << "ld_r16_imm16" << std::endl;
		ld_r16_imm16();
	}
	// 0x02 (BC), 0x12 (DE), 0x22 (HL+), 0x32 (HL-)
	else if ((code & 0b11001111) == 0b00000010)
	{
		std::cout << "ld_r16mem_a" << std::endl;
		ld_r16mem_a();
	}
	// 0x0A (BC), 0x1A (DE), 0x2A (HL+), 0x3A (HL-)
	else if ((code & 0b11001111) == 0b00001010)
	{
		std::cout << "ld_a_r16mem" << std::endl;
		ld_a_r16mem();
	}
	// Ox08
	else if (code == 0b00001000)
	{
		std::cout << "ld_imm16_sp" << std::endl;
		ld_imm16_sp();
	}
	// 0x03 (BC), 0x13 (DE), 0x23 (HL), 0x33 (SP)
	else if ((code & 0b11001111) == 0b00000011)
	{
		std::cout << "inc_r16" << std::endl;
		inc_r16();
	}
	// 0x0B (BC), 0x1B (DE), 0x2B (HL), 0x3B (SP)
	else if ((code & 0b11001111) == 0b00001011)
	{
		std::cout << "dec_r16" << std::endl;
		dec_r16();
	}
	// 0x09 (BC), 0x19 (DE), 0x29 (HL), 0x39 (SP)
	else if ((code & 0b11001111) == 0b00001001)
	{
		std::cout << "add_hl_r16" << std::endl;
		add_hl_r16();
	}
	// 0x04 (B), 0x0C (C), 0x14 (D), 0x1C (E), 0x24 (H), 0x2C (L), 0x34 (HL), 0x3C (A)
	else if ((code & 0b11000111) == 0b00000100)
	{
		std::cout << "inc_r8" << std::endl;
		inc_r8();
	}
	// 0x05 (B), 0x0D (C), 0x15 (D), 0x1D (E), 0x25 (H), 0x2D (L), 0x35 (HL), 0x3D (A)
	else if ((code & 0b11000111) == 0b00000101)
	{
		std::cout << "dec_r8" << std::endl;
		dec_r8();
	}
	// 0x06 (B), 0x0E (C), 0x16 (D), 0x1E (E), 0x26 (H), 0x2E (L), 0x36 (HL), 0x3E (A)
	else if ((code & 0b11000111) == 0b00000110)
	{
		std::cout << "ld_r8_imm8" << std::endl;
		ld_r8_imm8();
	}
	// 0x07
	else if (code == 0b00000111)
	{
		std::cout << "rlca" << std::endl;
		rlca();
	}
	// 0x0F
	else if (code == 0b00001111)
	{
		std::cout << "rrca" << std::endl;
		rrca();
	}
	// 0x17
	else if (code == 0b00010111)
	{
		std::cout << "rla" << std::endl;
		rla();
	}
	// 0x1F
	else if (code == 0b00011111)
	{
		std::cout << "rra" << std::endl;
		rra();
	}
	// 0x27
	else if (code == 0b00100111)
	{
		std::cout << "daa" << std::endl;
		daa();
	}
	// 0x2F
	else if (code == 0b00101111)
	{
		std::cout << "cpl" << std::endl;
		cpl();
	}
	// 0x37
	else if (code == 0b00110111)
	{
		std::cout << "scf" << std::endl;
		scf();
	}
	// 0x3F
	else if (code == 0b00111111)
	{
		std::cout << "ccf" << std::endl;
		ccf();
	}
	// 0x18
	else if (code == 0b00011000)
	{
		std::cout << "jr_imm8" << std::endl;
		jr_imm8();
	}
	// 0x20 (NZ), 0x28 (Z), 0x30 (NC), 0x38 (C)
	else if ((code & 0b11100111) == 0b00100000)
	{
		std::cout << "jr_cond_imm8" << std::endl;
		jr_cond_imm8();
	}
	// 0x10
	else if (code == 0b00010000)
	{
		std::cout << "stop" << std::endl;
		stop();
	}
	// Block 1 : 8-bit reg to reg loads
	// 0x40 (B/B), 0x41 (B/C), 0x42 (B/D), 0x43 (B/E), 0x44 (B/H), Ox45 (B/L), Ox46 (B/HL), Ox47 (B/A)
	// 0x48 (C/B), 0x49 (C/C), 0x4A (C/D), 0x4B (C/E), 0x4C (C/H), Ox4D (C/L), Ox4E (C/HL), Ox4F (C/A)
	// 0x50 (D/B), 0x51 (D/C), 0x52 (D/D), 0x53 (D/E), 0x54 (D/H), Ox55 (D/L), Ox56 (D/HL), Ox57 (D/A)
	// 0x58 (E/B), 0x59 (E/C), 0x5A (E/D), 0x5B (E/E), 0x5C (E/H), Ox5D (E/L), Ox5E (E/HL), Ox5F (E/A)
	// 0x60 (H/B), 0x61 (H/C), 0x62 (H/D), 0x63 (H/E), 0x64 (H/H), Ox65 (H/L), Ox66 (H/HL), Ox67 (H/A)
	// 0x68 (L/B), 0x69 (L/C), 0x6A (L/D), 0x6B (L/E), 0x6C (L/H), Ox6D (L/L), Ox6E (L/HL), Ox6F (L/A)
	// 0x70 (HL/B), 0x71 (HL/C), 0x72 (HL/D), 0x73 (HL/E), 0x74 (HL/H), Ox75 (HL/L), NO 0x76 (Used as halt), Ox77 (HL/A)
	// 0x78 (A/B), 0x79 (A/C), 0x7A (A/D), 0x7B (A/E), 0x7C (A/H), Ox7D (A/L), Ox7E (A/HL), Ox7F (A/A)
	else if ((code & 0b11000000) == 0b01000000 && code != 0b01110110)
	{
		std::cout << "ld_r8_r8" << std::endl;
		ld_r8_r8();
	}
	// 0x76
	else if (code == 0b01110110)
	{
		std::cout << "halt" << std::endl;
		halt();
	}
	// Block 2 : 8-bit arithmetic
	// 0x80 (B), 0x81 (C), 0x82 (D), 0x83 (E), 0x84 (H), Ox85 (L), Ox86 (HL), 0x87 (A)
	else if ((code & 0b11111000) == 0b10000000)
	{
		std::cout << "add_a_r8" << std::endl;
		add_a_r8();
	}
	// 0x88 (B), 0x89 (C), 0x8A (D), 0x8B (E), 0x8C (H), Ox8D (L), Ox8E (HL), 0x8F (A)
	else if ((code & 0b11111000) == 0b10001000)
	{
		std::cout << "adc_a_r8" << std::endl;
		adc_a_r8();
	}
	// 0x90 (B), 0x91 (C), 0x92 (D), 0x93 (E), 0x94 (H), Ox95 (L), Ox96 (HL), 0x97 (A)
	else if ((code & 0b11111000) == 0b10010000)
	{
		std::cout << "sub_a_r8" << std::endl;
		sub_a_r8();
	}
	// 0x98 (B), 0x99 (C), 0x9A (D), 0x9B (E), 0x9C (H), Ox9D (L), Ox9E (HL), 0x9F (A)
	else if ((code & 0b11111000) == 0b10011000)
	{
		std::cout << "sbc_a_r8" << std::endl;
		sbc_a_r8();
	}
	// 0xA0 (B), 0xA1 (C), 0xA2 (D), 0xA3 (E), 0xA4 (H), OxA5 (L), OxA6 (HL), 0xA7 (A)
	else if ((code & 0b11111000) == 0b10100000)
	{
		std::cout << "and_a_r8" << std::endl;
		and_a_r8();
	}
	// 0xA8 (B), 0xA9 (C), 0xAA (D), 0xAB (E), 0xAC (H), OxAD (L), OxAE (HL), 0xAF (A)
	else if ((code & 0b11111000) == 0b10101000)
	{
		std::cout << "xor_a_r8" << std::endl;
		xor_a_r8();
	}
	// 0xB0 (B), 0xB1 (C), 0xB2 (D), 0xB3 (E), 0xB4 (H), OxB5 (L), OxB6 (HL), 0xB7 (A)
	else if ((code & 0b11111000) == 0b10110000)
	{
		std::cout << "or_a_r8" << std::endl;
		or_a_r8();
	}
	// 0xB8 (B), 0xB9 (C), 0xBA (D), 0xBB (E), 0xBC (H), OxBD (L), OxBE (HL), 0xBF (A)
	else if ((code & 0b11111000) == 0b10111000)
	{
		std::cout << "cp_a_r8" << std::endl;
		cp_a_r8();
	}
	// Block 3
	// 0xC6
	else if (code == 0b11000110)
	{
		std::cout << "add_a_imm8" << std::endl;
		adc_a_imm8();
	}
	// 0xCE
	else if (code == 0b11001110)
	{
		std::cout << "adc_a_imm8" << std::endl;
		adc_a_imm8();
	}
	// 0xD6
	else if (code == 0b11010110)
	{
		std::cout << "sub_a_imm8" << std::endl;
		sub_a_imm8();
	}
	// 0xDE
	else if (code == 0b11011110)
	{
		std::cout << "sbc_a_imm8" << std::endl;
		sbc_a_imm8();
	}
	// 0xE6
	else if (code == 0b11100110)
	{
		std::cout << "and_a_imm8" << std::endl;
		and_a_imm8();
	}
	// 0xEE
	else if (code == 0b11101110)
	{
		std::cout << "xor_a_imm8" << std::endl;
		xor_a_imm8();
	}
	// 0xF6
	else if (code == 0b11110110)
	{
		std::cout << "or_a_imm8" << std::endl;
		or_a_imm8();
	}
	// 0xFE
	else if (code == 0b11111110)
	{
		std::cout << "cp_a_imm8" << std::endl;
		cp_a_imm8();
	}
	// 0xC0 (NZ), 0xC8 (Z), 0xD0 (NC), 0xD8 (C)
	else if ((code & 0b11100111) == 0b11000000)
	{
		std::cout << "ret_cond" << std::endl;
		ret_cond();
	}
	// 0xC9
	else if (code == 0b11001001)
	{
		std::cout << "ret" << std::endl;
		ret();
	}
	// 0xD9
	else if (code == 0b11011001)
	{
		std::cout << "reti" << std::endl;
		reti();
	}
	// 0xC2 (NZ), 0xCA (Z), 0xD2 (NC), 0xDA (C)
	else if ((code & 0b11100111) == 0b11000010)
	{
		std::cout << "jp_cond_imm16" << std::endl;
		jp_cond_imm16();
	}
	// 0xC3
	else if (code == 0b11000011)
	{
		std::cout << "jp_imm16" << std::endl;
		jp_imm16();
	}
	// 0xE9
	else if (code == 0b11101001)
	{
		std::cout << "jp_hl" << std::endl;
		jp_hl();
	}
	// 0xC4 (NZ), 0xCC (Z), 0xD4 (NC), 0xDC (C)
	else if ((code & 0b11100111) == 0b11000100)
	{
		std::cout << "call_cond_imm16" << std::endl;
		call_cond_imm16();
	}
	// 0xCD
	else if (code == 0b11001101)
	{
		std::cout << "call_imm16" << std::endl;
		call_imm16();
	}
	// 0xC4 (NZ), 0xCC (Z), 0xD4 (NC), 0xDC (C)
	else if ((code & 0b11100111) == 0b11000100)
	{
		std::cout << "call_cond_imm16" << std::endl;
		call_cond_imm16();
	}
	// 0xC7 (00H), 0xCF (08H), 0xD7 (10H), 0xDF (18H), 0xE7 (20H), OxEF (28H), OxF7 (30H), OxFF (38H)
	else if ((code & 0b11000111) == 0b11000111)
	{
		std::cout << "rst tgt3" << std::endl;
		rst_tgt3();
	}
	// 0xC1 (BC), 0xD1 (DE), 0xE1 (HL), OxF1 (SP)
	else if ((code & 0b11001111) == 0b11000001)
	{
		std::cout << "pop_r16stk" << std::endl;
		pop_r16stk();
	}
	// 0xC5 (BC), 0xD5 (DE), 0xE5 (HL), OxF5 (SP)
	else if ((code & 0b11001111) == 0b11000101)
	{
		std::cout << "push_r16stk" << std::endl;
		push_r16stk();
	}
	// 0xCB prefix
	else if (code == 0b11001011)
	{
		std::cout << "0xCB prefix" << std::endl;
		// TODO
	}
	// 0xE2
	else if (code == 0b11100010)
	{
		std::cout << "ldh_c_a" << std::endl;
		ldh_c_a();
	}
	// 0xE0
	else if (code == 0b11100000)
	{
		std::cout << "ldh_imm8_a" << std::endl;
		ldh_imm8_a();
	}
	// 0xE6
	else if (code == 0b11101010)
	{
		std::cout << "ld_imm16_a" << std::endl;
		ld_imm16_a();
	}
	// 0xF2
	else if (code == 0b11110010)
	{
		std::cout << "ldh_a_c" << std::endl;
		ldh_a_c();
	}
	// 0xF0
	else if (code == 0b11110000)
	{
		std::cout << "ldh_a_imm8" << std::endl;
		ldh_a_imm8();
	}
	// 0xF6
	else if (code == 0b11111010)
	{
		std::cout << "ld_a_imm16" << std::endl;
		ld_a_imm16();
	}
	// 0xE8
	else if (code == 0b11101000)
	{
		std::cout << "add_sp_imm8" << std::endl;
		add_sp_imm8();
	}
	// 0xF8
	else if (code == 0b11111000)
	{
		std::cout << "ld_hl_sp_imm8" << std::endl;
		ld_hl_sp_imm8();
	}
	// 0xF9
	else if (code == 0b11111001)
	{
		std::cout << "ld_sp_hl" << std::endl;
		ld_sp_hl();
	}
	// 0xF3
	else if (code == 0b11110011)
	{
		std::cout << "di" << std::endl;
		di();
	}
	// 0xFB
	else if (code == 0b11111011)
	{
		std::cout << "ei" << std::endl;
		ei();
	}
	else if (code == 0xD3 || code == 0xDB || code == 0xDD ||
			 code == 0xE3 || code == 0xE4 || code == 0xEB ||
			 code == 0xEC || code == 0xED || code == 0xF4 ||
			 code == 0xFC || code == 0xFD)
	{
		throw std::runtime_error(std::string("Invalid op code " + Common::toHexStr(code)));
	}
	else
	{
		throw std::runtime_error(std::string("Op code " + Common::toHexStr(code) + " not managed"));
	}
}

/**************************************/
/**              Block 0             **/
/**************************************/
void CPU::nop()
{
	ctx.regs().pc++;
}

void CPU::ld_r16_imm16()
{
	u16 imm16 = ctx.regs().imm16();

	R16 r16 = Registers::getR16FromCode((ctx.opCode() & 0b110000) >> 4);
	ctx.regs().setRegFromR16(r16, imm16);

	std::cout << "ld_r16_imm16 : " << Common::toHexStr(imm16) << " set to " << R16_STR[(int)r16] << std::endl;

	ctx.regs().pc += 3;
}

void CPU::ld_r16mem_a()
{
	R16_MEM r16Mem = Registers::getR16MemFromCode((ctx.opCode() & 0b110000) >> 4);
	u16 address = ctx.regs().getPointerFromR16Mem(r16Mem);
	ctx.mem().at(address) = ctx.regs().a;

	// HLI or HLD -> update HL after writing
	ctx.regs().updateHLMem(r16Mem);

	std::cout << "ld_r16mem_a : " << Common::toHexStr(ctx.regs().a) << " set to address " << Common::toHexStr(address) << " from register " << R16_STR[(int)r16Mem] << std::endl;

	ctx.regs().pc++;
}

void CPU::ld_a_r16mem()
{
}

void CPU::ld_imm16_sp()
{
}

void CPU::inc_r16()
{
}

void CPU::dec_r16()
{
}

void CPU::add_hl_r16()
{
}

void CPU::inc_r8()
{
}

void CPU::dec_r8()
{
	R8 r8 = Registers::getR8FromCode((ctx.opCode() & 0b111000) >> 3);
	ctx.regs().setRegFromR8(r8, ctx.regs().getFromR8(r8) - 1);

	ctx.regs().setFlags(ctx.regs().getFromR8(r8) == 0, 1, (ctx.regs().getFromR8(r8) & 0xF) == 0xF, -1);

	std::cout << "dec_r8 : " << R8_STR[(int)r8] << " decremented" << std::endl;
	ctx.regs().pc++;
}

void CPU::ld_r8_imm8()
{
	u8 imm8 = ctx.regs().imm8();

	R8 r8 = Registers::getR8FromCode((ctx.opCode() & 0b111000) >> 3);
	ctx.regs().setRegFromR8(r8, imm8);

	std::cout << "ld_r8_imm8 : " << Common::toHexStr(imm8) << " set to " << R8_STR[(int)r8] << std::endl;

	ctx.regs().pc += 2;
}

void CPU::rlca()
{
}

void CPU::rrca()
{
}

void CPU::rla()
{
}

void CPU::rra()
{
}

void CPU::daa()
{
}

void CPU::cpl()
{
}

void CPU::scf()
{
}

void CPU::ccf()
{
}

void CPU::jr_imm8()
{
}

void CPU::jr_cond_imm8()
{
}

void CPU::stop()
{
}

/**************************************/
/** Block 1 : 8-bit reg to reg loads **/
/**************************************/
void CPU::ld_r8_r8()
{
}

void CPU::halt()
{
}
/**************************************/
/**     Block 2 : 8-bit arithmetic   **/
/**************************************/
void CPU::add_a_r8()
{
}

void CPU::adc_a_r8()
{
}

void CPU::sub_a_r8()
{
}

void CPU::sbc_a_r8()
{
}

void CPU::and_a_r8()
{
}

void CPU::xor_a_r8()
{
	R8 r8 = Registers::getR8FromCode(ctx.opCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	ctx.regs().a ^= r8Value;

	ctx.regs().setFlags(ctx.regs().a == 0, 0, 0, 0);

	std::cout << "xor_a_r8 with " << R8_STR[(int)r8] << std::endl;
	ctx.regs().pc++;
}

void CPU::or_a_r8()
{
}

void CPU::cp_a_r8()
{
}
/**************************************/
/**              Block 3             **/
/**************************************/
void CPU::add_a_imm8()
{
}

void CPU::adc_a_imm8()
{
}

void CPU::sub_a_imm8()
{
}

void CPU::sbc_a_imm8()
{
}

void CPU::and_a_imm8()
{
}

void CPU::xor_a_imm8()
{
}

void CPU::or_a_imm8()
{
}

void CPU::cp_a_imm8()
{
}

void CPU::ret_cond()
{
}

void CPU::ret()
{
}

void CPU::reti()
{
}

void CPU::jp_cond_imm16()
{
}

void CPU::jp_imm16()
{
	u16 imm16 = ctx.regs().imm16();
	// JP to address given
	ctx.regs().pc = imm16;
	std::cout << "jp_imm16 : " << Common::toHexStr(imm16) << std::endl;
}

void CPU::jp_hl()
{
}

void CPU::call_cond_imm16()
{
}

void CPU::call_imm16()
{
}

void CPU::rst_tgt3()
{
}

void CPU::pop_r16stk()
{
}

void CPU::push_r16stk()
{
}

void CPU::prefix()
{
}

void CPU::ldh_c_a()
{
}

void CPU::ldh_imm8_a()
{
}

void CPU::ld_imm16_a()
{
}

void CPU::ldh_a_c()
{
}

void CPU::ldh_a_imm8()
{
}

void CPU::ld_a_imm16()
{
}

void CPU::add_sp_imm8()
{
}

void CPU::ld_hl_sp_imm8()
{
}

void CPU::ld_sp_hl()
{
}

void CPU::di()
{
}

void CPU::ei()
{
}

/**************************************/
/**           $CB prefix             **/
/**************************************/