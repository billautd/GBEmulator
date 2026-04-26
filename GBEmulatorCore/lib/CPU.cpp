#include <CPU.h>
#include <Context.h>

#define CPU_DEBUG true

CPU::CPU(Context &ctx) : ctx(ctx)
{
}

CPU::~CPU()
{
}

void CPU::runOp()
{
#if CPU_DEBUG
	std::cout << std::endl;
	std::cout << ctx.regs().log() << std::endl;
#endif

	// Read opcode and increase PC
	u8 code = ctx.mem().at(ctx.regs().pc);
	ctx.regs().pc++;
	setCurrentOpCode(code);

#if CPU_DEBUG
	std::cout << std::format("Current op code : {}\n", Common::toHexStr(code));
#endif

	// Block 0
	// 0x00
	if (code == 0)
		nop();
	// 0x01 (BC), 0x11 (DE), 0x21 (HL), 0x31 (SP)
	else if ((code & 0b11001111) == 0b00000001)
		ld_r16_imm16();
	// 0x02 (BC), 0x12 (DE), 0x22 (HL+), 0x32 (HL-)
	else if ((code & 0b11001111) == 0b00000010)
		ld_r16mem_a();
	// 0x0A (BC), 0x1A (DE), 0x2A (HL+), 0x3A (HL-)
	else if ((code & 0b11001111) == 0b00001010)
		ld_a_r16mem();
	// 0x08
	else if (code == 0b00001000)
		ld_imm16_sp();
	// 0x03 (BC), 0x13 (DE), 0x23 (HL), 0x33 (SP)
	else if ((code & 0b11001111) == 0b00000011)
		inc_r16();
	// 0x0B (BC), 0x1B (DE), 0x2B (HL), 0x3B (SP)
	else if ((code & 0b11001111) == 0b00001011)
		dec_r16();
	// 0x09 (BC), 0x19 (DE), 0x29 (HL), 0x39 (SP)
	else if ((code & 0b11001111) == 0b00001001)
		add_hl_r16();
	// 0x04 (B), 0x0C (C), 0x14 (D), 0x1C (E), 0x24 (H), 0x2C (L), 0x34 (HL), 0x3C (A)
	else if ((code & 0b11000111) == 0b00000100)
		inc_r8();
	// 0x05 (B), 0x0D (C), 0x15 (D), 0x1D (E), 0x25 (H), 0x2D (L), 0x35 (HL), 0x3D (A)
	else if ((code & 0b11000111) == 0b00000101)
		dec_r8();
	// 0x06 (B), 0x0E (C), 0x16 (D), 0x1E (E), 0x26 (H), 0x2E (L), 0x36 (HL), 0x3E (A)
	else if ((code & 0b11000111) == 0b00000110)
		ld_r8_imm8();
	// 0x07
	else if (code == 0b00000111)
		rlca();
	// 0x0F
	else if (code == 0b00001111)
		rrca();
	// 0x17
	else if (code == 0b00010111)
		rla();
	// 0x1F
	else if (code == 0b00011111)
		rra();
	// 0x27
	else if (code == 0b00100111)
		daa();
	// 0x2F
	else if (code == 0b00101111)
		cpl();
	// 0x37
	else if (code == 0b00110111)
		scf();
	// 0x3F
	else if (code == 0b00111111)
		ccf();
	// 0x18
	else if (code == 0b00011000)
		jr_imm8();
	// 0x20 (NZ), 0x28 (Z), 0x30 (NC), 0x38 (C)
	else if ((code & 0b11100111) == 0b00100000)
		jr_cond_imm8();
	// 0x10
	else if (code == 0b00010000)
		stop();
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
		ld_r8_r8();
	// 0x76
	else if (code == 0b01110110)
		halt();
	// Block 2 : 8-bit arithmetic
	// 0x80 (B), 0x81 (C), 0x82 (D), 0x83 (E), 0x84 (H), Ox85 (L), Ox86 (HL), 0x87 (A)
	else if ((code & 0b11111000) == 0b10000000)
		add_a_r8();
	// 0x88 (B), 0x89 (C), 0x8A (D), 0x8B (E), 0x8C (H), Ox8D (L), Ox8E (HL), 0x8F (A)
	else if ((code & 0b11111000) == 0b10001000)
		adc_a_r8();
	// 0x90 (B), 0x91 (C), 0x92 (D), 0x93 (E), 0x94 (H), Ox95 (L), Ox96 (HL), 0x97 (A)
	else if ((code & 0b11111000) == 0b10010000)
		sub_a_r8();
	// 0x98 (B), 0x99 (C), 0x9A (D), 0x9B (E), 0x9C (H), Ox9D (L), Ox9E (HL), 0x9F (A)
	else if ((code & 0b11111000) == 0b10011000)
		sbc_a_r8();
	// 0xA0 (B), 0xA1 (C), 0xA2 (D), 0xA3 (E), 0xA4 (H), OxA5 (L), OxA6 (HL), 0xA7 (A)
	else if ((code & 0b11111000) == 0b10100000)
		and_a_r8();
	// 0xA8 (B), 0xA9 (C), 0xAA (D), 0xAB (E), 0xAC (H), OxAD (L), OxAE (HL), 0xAF (A)
	else if ((code & 0b11111000) == 0b10101000)
		xor_a_r8();
	// 0xB0 (B), 0xB1 (C), 0xB2 (D), 0xB3 (E), 0xB4 (H), OxB5 (L), OxB6 (HL), 0xB7 (A)
	else if ((code & 0b11111000) == 0b10110000)
		or_a_r8();
	// 0xB8 (B), 0xB9 (C), 0xBA (D), 0xBB (E), 0xBC (H), OxBD (L), OxBE (HL), 0xBF (A)
	else if ((code & 0b11111000) == 0b10111000)
		cp_a_r8();
	// Block 3
	// 0xC6
	else if (code == 0b11000110)
		add_a_imm8();
	// 0xCE
	else if (code == 0b11001110)
		adc_a_imm8();
	// 0xD6
	else if (code == 0b11010110)
		sub_a_imm8();
	// 0xDE
	else if (code == 0b11011110)
		sbc_a_imm8();
	// 0xE6
	else if (code == 0b11100110)
		and_a_imm8();
	// 0xEE
	else if (code == 0b11101110)
		xor_a_imm8();
	// 0xF6
	else if (code == 0b11110110)
		or_a_imm8();
	// 0xFE
	else if (code == 0b11111110)
		cp_a_imm8();
	// 0xC0 (NZ), 0xC8 (Z), 0xD0 (NC), 0xD8 (C)
	else if ((code & 0b11100111) == 0b11000000)
		ret_cond();
	// 0xC9
	else if (code == 0b11001001)
		ret();
	// 0xD9
	else if (code == 0b11011001)
		reti();
	// 0xC2 (NZ), 0xCA (Z), 0xD2 (NC), 0xDA (C)
	else if ((code & 0b11100111) == 0b11000010)
		jp_cond_imm16();
	// 0xC3
	else if (code == 0b11000011)
		jp_imm16();
	// 0xE9
	else if (code == 0b11101001)
		jp_hl();
	// 0xC4 (NZ), 0xCC (Z), 0xD4 (NC), 0xDC (C)
	else if ((code & 0b11100111) == 0b11000100)
		call_cond_imm16();
	// 0xCD
	else if (code == 0b11001101)
		call_imm16();
	// 0xC4 (NZ), 0xCC (Z), 0xD4 (NC), 0xDC (C)
	else if ((code & 0b11100111) == 0b11000100)
		call_cond_imm16();
	// 0xC7 (00H), 0xCF (08H), 0xD7 (10H), 0xDF (18H), 0xE7 (20H), OxEF (28H), OxF7 (30H), OxFF (38H)
	else if ((code & 0b11000111) == 0b11000111)
		rst_tgt3();
	// 0xC1 (BC), 0xD1 (DE), 0xE1 (HL), OxF1 (SP)
	else if ((code & 0b11001111) == 0b11000001)
		pop_r16stk();
	// 0xC5 (BC), 0xD5 (DE), 0xE5 (HL), OxF5 (SP)
	else if ((code & 0b11001111) == 0b11000101)
		push_r16stk();
	// 0xCB prefix
	else if (code == 0b11001011)
	{
		// TODO
	}
	// 0xE2
	else if (code == 0b11100010)
		ldh_c_a();
	// 0xE0
	else if (code == 0b11100000)
		ldh_imm8_a();
	// 0xEA
	else if (code == 0b11101010)
		ld_imm16_a();
	// 0xF2
	else if (code == 0b11110010)
		ldh_a_c();
	// 0xF0
	else if (code == 0b11110000)
		ldh_a_imm8();
	// 0xF6
	else if (code == 0b11111010)
		ld_a_imm16();
	// 0xE8
	else if (code == 0b11101000)
		add_sp_imm8();
	// 0xF8
	else if (code == 0b11111000)
		ld_hl_sp_imm8();
	// 0xF9
	else if (code == 0b11111001)
		ld_sp_hl();
	// 0xF3
	else if (code == 0b11110011)
		di();
	// 0xFB
	else if (code == 0b11111011)
		ei();
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
	// Nothing
#if CPU_DEBUG
	std::cout << "nop" << std::endl;
#endif
}

void CPU::ld_r16_imm16()
{
	u16 imm16 = ctx.regs().imm16();

	R16 r16 = Registers::getR16FromCode((opCode() & 0b00110000) >> 4);
	ctx.regs().setRegFromR16(r16, imm16);

#if CPU_DEBUG
	std::cout << std::format("ld_r16_imm16 : {} set to {}\n", Common::toHexStr(imm16), R16_STR[(int)r16]);
#endif
}

void CPU::ld_r16mem_a()
{
	R16_MEM r16Mem = Registers::getR16MemFromCode((opCode() & 0b00110000) >> 4);
	u16 address = ctx.regs().getPointerFromR16Mem(r16Mem);
	ctx.mem().at(address) = ctx.regs().a;

	// HLI or HLD -> update HL after writing
	ctx.regs().updateHLMem(r16Mem);

#if CPU_DEBUG
	std::cout << std::format("ld_a_r16mem : Address {} set to {}from register {}\n", Common::toHexStr(address), Common::toHexStr(ctx.regs().a), R16_STR[(int)r16Mem]);
#endif
}

void CPU::ld_a_r16mem()
{
	R16_MEM r16Mem = Registers::getR16MemFromCode((opCode() & 0b00110000) >> 4);
	u16 address = ctx.regs().getPointerFromR16Mem(r16Mem);
	ctx.regs().a = ctx.mem().at(address);

	// HLI or HLD -> update HL after writing
	ctx.regs().updateHLMem(r16Mem);

#if CPU_DEBUG
	std::cout << std::format("ld_r16mem_a : {} set to address {} from register {}\n", Common::toHexStr(ctx.regs().a), Common::toHexStr(address), R16_STR[(int)r16Mem]);
#endif
}

void CPU::ld_imm16_sp()
{
	std::cout << "ld_imm16_sp not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::inc_r16()
{
	std::cout << "inc_r16 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::dec_r16()
{
	R16 r16 = Registers::getR16FromCode((opCode() & 0b00110000) >> 4);
	u16 r16Value = ctx.regs().getFromR16(r16);
	ctx.regs().setRegFromR16(r16, r16Value - 1);

#if CPU_DEBUG
	std::cout << std::format("dec_r16 : {} decremented to {}\n", R16_STR[(int)r16], Common::toHexStr(ctx.regs().getFromR16(r16)));
#endif
}

void CPU::add_hl_r16()
{
	std::cout << "add_hl_r16 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::inc_r8()
{
	R8 r8 = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
	u8 r8Value = ctx.regs().getFromR8(r8);
	ctx.regs().setRegFromR8(r8, r8Value + 1);

	u8 newValue = ctx.regs().getFromR8(r8);

	ctx.regs().setFlags(newValue == 0, 0, (r8Value & 0xF) == 0xF, -1);

#if CPU_DEBUG
	std::cout << std::format("dec_r8 : {} decremented to {}\n", R8_STR[(int)r8], Common::toHexStr(newValue));
#endif
}

void CPU::dec_r8()
{
	R8 r8 = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
	u8 r8Value = ctx.regs().getFromR8(r8);
	ctx.regs().setRegFromR8(r8, r8Value - 1);

	u8 newValue = ctx.regs().getFromR8(r8);

	ctx.regs().setFlags(newValue == 0, 1, (r8Value & 0xF) == 0, -1);

#if CPU_DEBUG
	std::cout << std::format("dec_r8 : {} decremented to {}\n", R8_STR[(int)r8], Common::toHexStr(newValue));
#endif
}

void CPU::ld_r8_imm8()
{
	u8 imm8 = ctx.regs().imm8();

	R8 r8 = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
	ctx.regs().setRegFromR8(r8, imm8);

#if CPU_DEBUG
	std::cout << std::format("ld_r8_imm8 with {} set to {}\n", Common::toHexStr(imm8), R8_STR[(int)r8]);
#endif
}

void CPU::rlca()
{
	std::cout << "rlca not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::rrca()
{
	std::cout << "rrca not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::rla()
{
	std::cout << "rla not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::rra()
{
	std::cout << "rra not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::daa()
{
	std::cout << "daa not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::cpl()
{
	std::cout << "cpl not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::scf()
{
	std::cout << "scf not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::ccf()
{
	std::cout << "ccf not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::jr_imm8()
{
	std::cout << "jr_imm8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::jr_cond_imm8()
{
	u8 imm8 = ctx.regs().imm8();
	COND cond = Registers::getCONDFromCode((opCode() & 0b00011000) >> 3);
	if (ctx.regs().checkCOND(cond))
	{
		// Value is signed, will jump after or before current PC
		ctx.regs().pc += (i8)imm8;
#if CPU_DEBUG
		std::cout << std::format("jr_cond_imm8 with {}, PC set to {}\n", Common::toHexStr(imm8), Common::toHexStr(ctx.regs().pc));
#endif
	}
	else
	{
#if CPU_DEBUG
		std::cout << std::format("jr_cond_imm8 with {}, PC unchanged\n", Common::toHexStr(imm8));
#endif
	}
}

void CPU::stop()
{
	std::cout << "stop not implemented" << std::endl;
	ctx.setRunning(false);
}

/**************************************/
/** Block 1 : 8-bit reg to reg loads **/
/**************************************/
void CPU::ld_r8_r8()
{
	R8 r8_src = Registers::getR8FromCode(opCode() & 0b111);
	R8 r8_dest = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
	ctx.regs().setRegFromR8(r8_dest, ctx.regs().getFromR8(r8_src));

#if CPU_DEBUG
	std::cout << std::format("ld_r8_r8 with {} set to {} value {}\n", R8_STR[(int)r8_dest], R8_STR[(int)r8_src], Common::toHexStr(ctx.regs().getFromR8(r8_src)));
#endif
}

void CPU::halt()
{
	std::cout << "halt not implemented" << std::endl;
	ctx.setRunning(false);
}
/**************************************/
/**     Block 2 : 8-bit arithmetic   **/
/**************************************/
void CPU::add_a_r8()
{
	std::cout << "add_a_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::adc_a_r8()
{
	std::cout << "adc_a_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::sub_a_r8()
{
	std::cout << "sub_a_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::sbc_a_r8()
{
	std::cout << "sbc_a_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::and_a_r8()
{
	std::cout << "and_a_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::xor_a_r8()
{
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);

	ctx.regs().a ^= r8Value;

	u8 newValue = ctx.regs().a;
	ctx.regs().setFlags(newValue == 0, 0, 0, 0);

#if CPU_DEBUG
	std::cout << std::format("xor_a_r8 with {}, A is {}\n", R8_STR[(int)r8], Common::toHexStr(ctx.regs().a));
#endif
}

void CPU::or_a_r8()
{
	std::cout << "or_a_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::cp_a_r8()
{
	std::cout << "cp_a_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}
/**************************************/
/**              Block 3             **/
/**************************************/
void CPU::add_a_imm8()
{
	std::cout << "add_a_imm8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::adc_a_imm8()
{
	std::cout << "adc_a_imm8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::sub_a_imm8()
{
	std::cout << "sub_a_imm8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::sbc_a_imm8()
{
	std::cout << "sbc_a_imm8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::and_a_imm8()
{
	std::cout << "and_a_imm8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::xor_a_imm8()
{
	std::cout << "xor_a_imm8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::or_a_imm8()
{
	std::cout << "or_a_imm8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::cp_a_imm8()
{
	u8 imm8 = ctx.regs().imm8();
	u8 a = ctx.regs().a;

	ctx.regs().setFlags((a - imm8) == 0, 1, (a & 0xF) < (imm8 & 0xF), a < imm8);

#if CPU_DEBUG
	std::cout << std::format("Comparing {} with {}\n", Common::toHexStr(a), Common::toHexStr(imm8));
#endif
}

void CPU::ret_cond()
{
	std::cout << "ret_cond not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::ret()
{
	std::cout << "ret not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::reti()
{
	std::cout << "reti not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::jp_cond_imm16()
{
	std::cout << "jp_cond_imm16 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::jp_imm16()
{
	u16 imm16 = ctx.regs().imm16();
	// JP to address given
	ctx.regs().pc = imm16;

#if CPU_DEBUG
	std::cout << std::format("jp_imm16 to {}\n", Common::toHexStr(imm16));
#endif
}

void CPU::jp_hl()
{
	std::cout << "jp_hl not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::call_cond_imm16()
{
	std::cout << "call_cond_imm16 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::call_imm16()
{
	u16 newPC = ctx.regs().imm16();

	// Set imm16 to stack
	ctx.regs().sp--;
	ctx.mem().at(ctx.regs().sp) = ctx.regs().pc >> 8;
	ctx.regs().sp--;
	ctx.mem().at(ctx.regs().sp) = ctx.regs().pc & 0XFF;

	ctx.regs().pc = newPC;

#if CPU_DEBUG
	std::cout << std::format("call_imm16 to {}\n", Common::toHexStr(newPC));
#endif
}

void CPU::rst_tgt3()
{
	std::cout << "rst_tgt3 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::pop_r16stk()
{
	std::cout << "pop_r16stk not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::push_r16stk()
{
	std::cout << "push_r16stk not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::prefix()
{
	std::cout << "prefix not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::ldh_c_a()
{
	u16 c = 0xFF00 | ctx.regs().c;
	ctx.mem().at(c) = ctx.regs().a;

#if CPU_DEBUG
	std::cout << std::format("ldh_c_a, addr {} set to {}\n", Common::toHexStr(c), Common::toHexStr(ctx.regs().a));
#endif
}

void CPU::ldh_imm8_a()
{
	u8 imm8 = ctx.regs().imm8();
	u16 a8 = 0xFF00 | imm8;
	ctx.mem().at(a8) = ctx.regs().a;

#if CPU_DEBUG
	std::cout << std::format("ldh_imm8_a, set {} to {}\n", Common::toHexStr(ctx.regs().a), Common::toHexStr(a8));
#endif
}

void CPU::ld_imm16_a()
{
	u16 imm16 = ctx.regs().imm16();
	ctx.mem().at(imm16) = ctx.regs().a;

#if CPU_DEBUG
	std::cout << std::format("ld_imm16_a, set {} to addr {}\n", Common::toHexStr(ctx.regs().a), Common::toHexStr(imm16));
#endif
}

void CPU::ldh_a_c()
{
	std::cout << "ldh_a_c not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::ldh_a_imm8()
{
	u8 imm8 = ctx.regs().imm8();
	u16 a8 = 0xFF00 | imm8;
	ctx.regs().a = ctx.mem().at(a8);

#if CPU_DEBUG
	std::cout << std::format("ldh_a_imm8, A set to {} from {}\n", Common::toHexStr(ctx.regs().a), Common::toHexStr(a8));
#endif
}

void CPU::ld_a_imm16()
{
	std::cout << "ld_a_imm16 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::add_sp_imm8()
{
	std::cout << "add_sp_imm8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::ld_hl_sp_imm8()
{
	std::cout << "ld_hl_sp_imm8 not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::ld_sp_hl()
{
	std::cout << "ld_sp_hl not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::di()
{
	setIME(false);
#if CPU_DEBUG
	std::cout << "di" << std::endl;
#endif
}

void CPU::ei()
{
	setIME(true);
#if CPU_DEBUG
	std::cout << "ei" << std::endl;
#endif
}

/**************************************/
/**           $CB prefix             **/
/**************************************/