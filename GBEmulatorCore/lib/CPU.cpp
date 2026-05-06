#include <CPU.h>
#include <Context.h>

#define CPU_DEBUG false

CPU::CPU(Context &ctx) : ctx(ctx), microOp(CPUMicroOp(ctx)), interrupts(Interrupts(ctx))
{
}

CPU::~CPU()
{
}

void CPU::tick()
{
	cycles++;
	// Stall T-cycles
	if (stallCycles > 0)
	{
		stallCycles--;
		return;
	}
	if (queue.empty())
	{
		fetchOp();
	}
	executeMicroOps();
	if (instructionJustFinished)
	{
		interrupts.handle();
	}
}

void CPU::fetchOp()
{
	// If queue empty, scheduling next CPU operation
	// Each instruction in queue = 4 T-Cycles = 1 M-Cycle
	pushToQueue({CPUMicroOpType::FETCH_DECODE_SCHEDULE}); // 4
}

void CPU::executeMicroOps()
{
	instructionJustFinished = false;

	// Pop next instruction in queue and run it, until CPU operation is fully processed (empty queue)
	// If instruction takes no cycle, go to next without waiting for tick
	while (!queue.empty())
	{
		CPUMicroOpStruct op = queue.front();
		if (stallCycles > 0 && op.cycles != 0)
			break;

		queue.pop();
		microOp.runMicroOp(op);

		// FIXME : If all cycles are 0, a cycle is consumed when it should not be
		if (op.cycles > 0 && stallCycles == 0)
			stall(op.cycles * 3);
		if (queue.empty())
		{
#if CPU_DEBUG
			std::cout << std::format("Cycle {} - {} => {}\n", Common::toHexStr(cycles + stallCycles), Common::toHexStr(currentOpCode), ctx.regs().log());
#endif
			instructionJustFinished = true;
		}
	}
}

void CPU::runOp(u8 code)
{
	std::cout << ctx.mem().readMem(0xFF01);
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
	// 0x40 (B/B), 0x41 (B/C), 0x42 (B/D), 0x43 (B/E), 0x44 (B/H), 0x45 (B/L), 0x46 (B/HL), 0x47 (B/A)
	// 0x48 (C/B), 0x49 (C/C), 0x4A (C/D), 0x4B (C/E), 0x4C (C/H), 0x4D (C/L), 0x4E (C/HL), 0x4F (C/A)
	// 0x50 (D/B), 0x51 (D/C), 0x52 (D/D), 0x53 (D/E), 0x54 (D/H), 0x55 (D/L), 0x56 (D/HL), 0x57 (D/A)
	// 0x58 (E/B), 0x59 (E/C), 0x5A (E/D), 0x5B (E/E), 0x5C (E/H), 0x5D (E/L), 0x5E (E/HL), 0x5F (E/A)
	// 0x60 (H/B), 0x61 (H/C), 0x62 (H/D), 0x63 (H/E), 0x64 (H/H), 0x65 (H/L), 0x66 (H/HL), 0x67 (H/A)
	// 0x68 (L/B), 0x69 (L/C), 0x6A (L/D), 0x6B (L/E), 0x6C (L/H), 0x6D (L/L), 0x6E (L/HL), 0x6F (L/A)
	// 0x70 (HL/B), 0x71 (HL/C), 0x72 (HL/D), 0x73 (HL/E), 0x74 (HL/H), 0x75 (HL/L), 0x77 (HL/A)
	// 0x78 (A/B), 0x79 (A/C), 0x7A (A/D), 0x7B (A/E), 0x7C (A/H), 0x7D (A/L), 0x7E (A/HL), 0x7F (A/A)
	else if ((code & 0b11000000) == 0b01000000 && code != 0b01110110)
		ld_r8_r8();
	// 0x76
	else if (code == 0b01110110)
		halt();
	// Block 2 : 8-bit arithmetic
	// 0x80 (B), 0x81 (C), 0x82 (D), 0x83 (E), 0x84 (H), 0x85 (L), 0x86 (HL), 0x87 (A)
	else if ((code & 0b11111000) == 0b10000000)
		add_a_r8();
	// 0x88 (B), 0x89 (C), 0x8A (D), 0x8B (E), 0x8C (H), 0x8D (L), 0x8E (HL), 0x8F (A)
	else if ((code & 0b11111000) == 0b10001000)
		adc_a_r8();
	// 0x90 (B), 0x91 (C), 0x92 (D), 0x93 (E), 0x94 (H), 0x95 (L), 0x96 (HL), 0x97 (A)
	else if ((code & 0b11111000) == 0b10010000)
		sub_a_r8();
	// 0x98 (B), 0x99 (C), 0x9A (D), 0x9B (E), 0x9C (H), 0x9D (L), 0x9E (HL), 0x9F (A)
	else if ((code & 0b11111000) == 0b10011000)
		sbc_a_r8();
	// 0xA0 (B), 0xA1 (C), 0xA2 (D), 0xA3 (E), 0xA4 (H), 0xA5 (L), 0xA6 (HL), 0xA7 (A)
	else if ((code & 0b11111000) == 0b10100000)
		and_a_r8();
	// 0xA8 (B), 0xA9 (C), 0xAA (D), 0xAB (E), 0xAC (H), 0xAD (L), 0xAE (HL), 0xAF (A)
	else if ((code & 0b11111000) == 0b10101000)
		xor_a_r8();
	// 0xB0 (B), 0xB1 (C), 0xB2 (D), 0xB3 (E), 0xB4 (H), 0xB5 (L), 0xB6 (HL), 0xB7 (A)
	else if ((code & 0b11111000) == 0b10110000)
		or_a_r8();
	// 0xB8 (B), 0xB9 (C), 0xBA (D), 0xBB (E), 0xBC (H), 0xBD (L), 0xBE (HL), 0xBF (A)
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
	// 0xC7 (00H), 0xCF (08H), 0xD7 (10H), 0xDF (18H), 0xE7 (20H), 0xEF (28H), 0xF7 (30H), 0xFF (38H)
	else if ((code & 0b11000111) == 0b11000111)
		rst_tgt3();
	// 0xC1 (BC), 0xD1 (DE), 0xE1 (HL), 0xF1 (SP)
	else if ((code & 0b11001111) == 0b11000001)
		pop_r16stk();
	// 0xC5 (BC), 0xD5 (DE), 0xE5 (HL), 0xF5 (SP)
	else if ((code & 0b11001111) == 0b11000101)
		push_r16stk();
	// 0xCB prefix
	else if (code == 0b11001011)
	{
		pushToQueue({CPUMicroOpType::FETCH_DECODE_SCHEDULE_CB_PREFIX});
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
	// 0xFA
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
		throw std::runtime_error(std::string("Invalid op code " + Common::toHexStr(code) + " from PC " + Common::toHexStr(ctx.regs().pc)));
	else
		throw std::runtime_error(std::string("Op code " + Common::toHexStr(code) + " not managed from PC " + Common::toHexStr(ctx.regs().pc)));
}

void CPU::runOpCBPrefix(u8 cbCode)
{
	// 0xCB00 (B), 0xCB01 (C), 0xCB02 (D), 0xCB03 (E), 0xCB04 (H), 0xCB05 (L), 0xCB06 (HL), 0xCB07 (A)
	if ((cbCode & 0b11111000) == 0b00000000)
		rlc_r8();
	// 0xCB08 (B), 0xCB09 (C), 0xCB0A (D), 0xCB0B (E), 0xCB0C (H), 0xCB0D (L), 0xCB0E (HL), 0xCB0F (A)
	else if ((cbCode & 0b11111000) == 0b00001000)
		rrc_r8();
	// 0xCB10 (B), 0xCB11 (C), 0xCB12 (D), 0xCB13 (E), 0xCB14 (H), 0xCB15 (L), 0xCB16 (HL), 0xCB17 (A)
	else if ((cbCode & 0b11111000) == 0b00010000)
		rl_r8();
	// 0xCB18 (B), 0xCB19 (C), 0xCB1A (D), 0xCB1B (E), 0xCB1C (H), 0xCB1D (L), 0xCB1E (HL), 0xCB1F (A)
	else if ((cbCode & 0b11111000) == 0b00011000)
		rr_r8();
	// 0xCB20 (B), 0xCB21 (C), 0xCB22 (D), 0xCB23 (E), 0xCB24 (H), 0xCB25 (L), 0xCB26 (HL), 0xCB27 (A)
	else if ((cbCode & 0b11111000) == 0b00100000)
		sla_r8();
	// 0xCB28 (B), 0xCB29 (C), 0xCB2A (D), 0xCB2B (E), 0xCB2C (H), 0xCB2D (L), 0xCB2E (HL), 0xCB2F (A)
	else if ((cbCode & 0b11111000) == 0b00101000)
		sra_r8();
	// 0xCB30 (B), 0xCB31 (C), 0xCB32 (D), 0xCB33 (E), 0xCB34 (H), 0xCB35 (L), 0xCB36 (HL), 0xCB37 (A)
	else if ((cbCode & 0b11111000) == 0b00110000)
		swap_r8();
	// 0xCB38 (B), 0xCB39 (C), 0xCB3A (D), 0xCB3B (E), 0xCB3C (H), 0xCB3D (L), 0xCB3E (HL), 0xCB3F (A)
	else if ((cbCode & 0b11111000) == 0b00111000)
		srl_r8();
	// 0xCB40 (0 / B),0xCB41 (0 / C), 0xCB42 (0 / D), 0xCB43 (0 / E), 0xCB44 (0 / H), 0xCB45 (0 / L), 0xCB46 (0 / HL), 0xCB47 (0 / A)
	// 0xCB48 (1 / B),0xCB49 (1 / C), 0xCB4A (1 / D), 0xCB4B (1 / E), 0xCB4C (1 / H), 0xCB4D (1 / L), 0xCB4E (1 / HL), 0xCB4F (1 / A)
	// 0xCB50 (2 / B),0xCB51 (2 / C), 0xCB52 (2 / D), 0xCB53 (2 / E), 0xCB54 (2 / H), 0xCB55 (2 / L), 0xCB56 (2 / HL), 0xCB57 (2 / A)
	// 0xCB58 (3 / B),0xCB59 (3 / C), 0xCB5A (3 / D), 0xCB5B (3 / E), 0xCB5C (3 / H), 0xCB5D (3 / L), 0xCB5E (3 / HL), 0xCB5F (3 / A)
	// 0xCB60 (4 / B),0xCB61 (4 / C), 0xCB62 (4 / D), 0xCB63 (4 / E), 0xCB64 (4 / H), 0xCB65 (4 / L), 0xCB66 (4 / HL), 0xCB67 (4 / A)
	// 0xCB68 (5 / B),0xCB69 (5 / C), 0xCB6A (5 / D), 0xCB6B (5 / E), 0xCB6C (5 / H), 0xCB6D (5 / L), 0xCB6E (5 / HL), 0xCB6F (5 / A)
	// 0xCB70 (6 / B),0xCB71 (6 / C), 0xCB72 (6 / D), 0xCB73 (6 / E), 0xCB74 (6 / H), 0xCB75 (6 / L), 0xCB76 (6 / HL), 0xCB77 (6 / A)
	// 0xCB78 (7 / B),0xCB79 (7 / C), 0xCB7A (7 / D), 0xCB7B (7 / E), 0xCB7C (7 / H), 0xCB7D (7 / L), 0xCB7E (7 / HL), 0xCB7F (7 / A)
	else if ((cbCode & 0b11000000) == 0b01000000)
		bit_b3_r8();
	// 0xCB80 (0 / B),0xCB81 (0 / C), 0xCB82 (0 / D), 0xCB83 (0 / E), 0xCB84 (0 / H), 0xCB85 (0 / L), 0xCB86 (0 / HL), 0xCB87 (0 / A)
	// 0xCB88 (1 / B),0xCB89 (1 / C), 0xCB8A (1 / D), 0xCB8B (1 / E), 0xCB8C (1 / H), 0xCB8D (1 / L), 0xCB8E (1 / HL), 0xCB8F (1 / A)
	// 0xCB90 (2 / B),0xCB91 (2 / C), 0xCB92 (2 / D), 0xCB93 (2 / E), 0xCB94 (2 / H), 0xCB95 (2 / L), 0xCB96 (2 / HL), 0xCB97 (2 / A)
	// 0xCB98 (3 / B),0xCB99 (3 / C), 0xCB9A (3 / D), 0xCB9B (3 / E), 0xCB9C (3 / H), 0xCB9D (3 / L), 0xCB9E (3 / HL), 0xCB9F (3 / A)
	// 0xCBA0 (4 / B),0xCBA1 (4 / C), 0xCBA2 (4 / D), 0xCBA3 (4 / E), 0xCBA4 (4 / H), 0xCBA5 (4 / L), 0xCBA6 (4 / HL), 0xCBA7 (4 / A)
	// 0xCBA8 (5 / B),0xCBA9 (5 / C), 0xCBAA (5 / D), 0xCBAB (5 / E), 0xCBAC (5 / H), 0xCBAD (5 / L), 0xCBAE (5 / HL), 0xCBAF (5 / A)
	// 0xCBB0 (6 / B),0xCBB1 (6 / C), 0xCBB2 (6 / D), 0xCBB3 (6 / E), 0xCBB4 (6 / H), 0xCBB5 (6 / L), 0xCBB6 (6 / HL), 0xCBB7 (6 / A)
	// 0xCBB8 (7 / B),0xCBB9 (7 / C), 0xCBBA (7 / D), 0xCBBB (7 / E), 0xCBBC (7 / H), 0xCBBD (7 / L), 0xCBBE (7 / HL), 0xCBBF (7 / A)
	else if ((cbCode & 0b11000000) == 0b10000000)
		res_b3_r8();
	// 0xCBC0 (0 / B),0xCBC1 (0 / C), 0xCBC2 (0 / D), 0xCBC3 (0 / E), 0xCBC4 (0 / H), 0xCBC5 (0 / L), 0xCBC6 (0 / HL), 0xCBC7 (0 / A)
	// 0xCBC8 (1 / B),0xCBC9 (1 / C), 0xCBCA (1 / D), 0xCBCB (1 / E), 0xCBCC (1 / H), 0xCBCD (1 / L), 0xCBCE (1 / HL), 0xCBCF (1 / A)
	// 0xCBD0 (2 / B),0xCBD1 (2 / C), 0xCBD2 (2 / D), 0xCBD3 (2 / E), 0xCBD4 (2 / H), 0xCBD5 (2 / L), 0xCBD6 (2 / HL), 0xCBD7 (2 / A)
	// 0xCBD8 (3 / B),0xCBD9 (3 / C), 0xCBDA (3 / D), 0xCBDB (3 / E), 0xCBDC (3 / H), 0xCBDD (3 / L), 0xCBDE (3 / HL), 0xCBDF (3 / A)
	// 0xCBE0 (4 / B),0xCBE1 (4 / C), 0xCBE2 (4 / D), 0xCBE3 (4 / E), 0xCBE4 (4 / H), 0xCBE5 (4 / L), 0xCBE6 (4 / HL), 0xCBE7 (4 / A)
	// 0xCBE8 (5 / B),0xCBE9 (5 / C), 0xCBEA (5 / D), 0xCBEB (5 / E), 0xCBEC (5 / H), 0xCBED (5 / L), 0xCBEE (5 / HL), 0xCBEF (5 / A)
	// 0xCBF0 (6 / B),0xCBF1 (6 / C), 0xCBF2 (6 / D), 0xCBF3 (6 / E), 0xCBF4 (6 / H), 0xCBF5 (6 / L), 0xCBF6 (6 / HL), 0xCBF7 (6 / A)
	// 0xCBF8 (7 / B),0xCBF9 (7 / C), 0xCBFA (7 / D), 0xCBFB (7 / E), 0xCBFC (7 / H), 0xCBFD (7 / L), 0xCBFE (7 / HL), 0xCBFF (7 / A)
	else if ((cbCode & 0b11000000) == 0b11000000)
		set_b3_r8();
	else
		throw std::runtime_error(std::string("Op code " + Common::toHexStr(cbCode) + "with CB prefix not managed"));
}

/**************************************/
/**              Block 0             **/
/**************************************/
// 4 ticks
void CPU::nop()
{
	// Nothing
}

// 12 ticks
void CPU::ld_r16_imm16()
{
	R16 r16 = Registers::getR16FromCode((opCode() & 0b00110000) >> 4);
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});									  // 4
	pushToQueue({CPUMicroOpType::READ_IMM8_HIGH});									  // 4
	pushToQueue({.type = CPUMicroOpType::WRITE_TMP_TO_R16, .cycles = 0, .r16 = r16}); // 0
}

// 8 ticks
void CPU::ld_r16mem_a()
{
	R16_MEM r16Mem = Registers::getR16MemFromCode((opCode() & 0b00110000) >> 4);
	pushToQueue({.type = CPUMicroOpType::WRITE_A_TO_R16MEM_ADDR, .r16Mem = r16Mem}); // 4
}

// 8 ticks
void CPU::ld_a_r16mem()
{
	R16_MEM r16Mem = Registers::getR16MemFromCode((opCode() & 0b00110000) >> 4);
	pushToQueue({.type = CPUMicroOpType::WRITE_R16MEM_ADDR_TO_A, .r16Mem = r16Mem}); // 4
}

// 20 ticks
void CPU::ld_imm16_sp()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});			  // 4
	pushToQueue({CPUMicroOpType::READ_IMM8_HIGH});			  // 4
	pushToQueue({CPUMicroOpType::WRITE_SP_LOW_TO_TMP_ADDR});  // 4
	pushToQueue({CPUMicroOpType::WRITE_SP_HIGH_TO_TMP_ADDR}); // 4
}

// 8 ticks
void CPU::inc_r16()
{
	R16 r16 = Registers::getR16FromCode((opCode() & 0b00110000) >> 4);
	pushToQueue({.type = CPUMicroOpType::INC_R16, .r16 = r16}); // 4
}

// 8 ticks
void CPU::dec_r16()
{
	R16 r16 = Registers::getR16FromCode((opCode() & 0b00110000) >> 4);
	pushToQueue({.type = CPUMicroOpType::DEC_R16, .r16 = r16}); // 4
}

// 8 ticks
void CPU::add_hl_r16()
{
	R16 r16 = Registers::getR16FromCode((opCode() & 0b00110000) >> 4);
	pushToQueue({.type = CPUMicroOpType::ADD_R16_TO_HL, .r16 = r16}); // 4
}

// 4 ticks if not (HL), 12 ticks if (HL)
void CPU::inc_r8()
{
	R8 r8 = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = R8::HL}); // 4
	pushToQueue({.type = CPUMicroOpType::INC_R8, .cycles = 0, .r8_dest = r8});	   // 0
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::WRITE_TMP_TO_R8, .r8_dest = R8::HL}); // 4
}

// 4 ticks if not (HL), 12 ticks if (HL)
void CPU::dec_r8()
{
	R8 r8 = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = R8::HL}); // 4
	pushToQueue({.type = CPUMicroOpType::DEC_R8, .cycles = 0, .r8_dest = r8});	   // 0
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::WRITE_TMP_TO_R8, .r8_dest = R8::HL}); // 4
}

// 8 ticks if not (HL), 12 ticks if (HL)
void CPU::ld_r8_imm8()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW}); // 4
	R8 r8 = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::WRITE_TMP_TO_R8, .cycles = 1, .r8_dest = R8::HL}); // 4
	else
		pushToQueue({.type = CPUMicroOpType::WRITE_TMP_TO_R8, .cycles = 0, .r8_dest = r8}); // 0
}

// 4 ticks
void CPU::rlca()
{
	pushToQueue({CPUMicroOpType::RLCA, 0}); // 0
}

// 4 ticks
void CPU::rrca()
{
	pushToQueue({CPUMicroOpType::RRCA, 0}); // 0
}

// 4 ticks
void CPU::rla()
{
	pushToQueue({CPUMicroOpType::RLA, 0}); // 0
}

// 4 ticks
void CPU::rra()
{
	pushToQueue({CPUMicroOpType::RRA, 0}); // 0
}

// 4 ticks
void CPU::daa()
{
	std::cout << "daa not implemented" << std::endl;
	ctx.setRunning(false);
}

// 4 ticks
void CPU::cpl()
{
	pushToQueue({CPUMicroOpType::CPL, 0});
}

// 4 ticks
void CPU::scf()
{
	pushToQueue({CPUMicroOpType::SCF, 0});
}

// 4 ticks
void CPU::ccf()
{
	pushToQueue({CPUMicroOpType::CCF, 0});
}

// 12 ticks
void CPU::jr_imm8()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW}); // 4
	pushToQueue({CPUMicroOpType::JR});			  // 4
}

// 8 ticks if cond false, 12 ticks if cond true
void CPU::jr_cond_imm8()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW}); // 4
	COND cond = Registers::getCONDFromCode((opCode() & 0b00011000) >> 3);
	pushToQueue({.type = CPUMicroOpType::JR_CONDITIONAL, .cycles = 0, .cond = cond}); // 0 or 4
}

// 4 ticks
void CPU::stop()
{
	std::cout << "stop not implemented" << std::endl;
	ctx.setRunning(false);
}

/**************************************/
/** Block 1 : 8-bit reg to reg loads **/
/**************************************/
// 4 ticks if r8 src and dest are not (HL), 8 ticks if r8 src or dest is (HL)
void CPU::ld_r8_r8()
{
	R8 r8_src = Registers::getR8FromCode(opCode() & 0b111);
	R8 r8_dest = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
	if ((r8_src == R8::HL) || (r8_dest == R8::HL))
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = r8_src, .r8_dest = r8_dest});	// 4
	pushToQueue({.type = CPUMicroOpType::LD_R8_R8, .cycles = 0, .r8_src = r8_src, .r8_dest = r8_dest}); // 4
}

// 4 ticks
void CPU::halt()
{
	std::cout << "halt not implemented" << std::endl;
	ctx.setRunning(false);
}
/**************************************/
/**     Block 2 : 8-bit arithmetic   **/
/**************************************/
// 4 ticks if not (HL), 8 ticks if (HL)
void CPU::add_a_r8()
{
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = R8::HL}); // 4
	pushToQueue({CPUMicroOpType::ADD_A_R8, 0, r8});								   // 0
}

// 4 ticks if not (HL), 8 ticks if (HL)
void CPU::adc_a_r8()
{
	std::cout << "adc_a_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}

// 4 ticks if not (HL), 8 ticks if (HL)
void CPU::sub_a_r8()
{
	std::cout << "sub_a_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}

// 4 ticks if not (HL), 8 ticks if (HL)
void CPU::sbc_a_r8()
{
	std::cout << "sbc_a_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}

// 4 ticks if not (HL), 8 ticks if (HL)
void CPU::and_a_r8()
{
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = R8::HL}); // 4
	pushToQueue({CPUMicroOpType::AND_A_R8, 0, r8});								   // 0
}

// 4 ticks if not (HL), 8 ticks if (HL)
void CPU::xor_a_r8()
{
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = R8::HL}); // 4
	pushToQueue({.type = CPUMicroOpType::XOR_A_R8, .cycles = 0, .r8_src = r8});	   // 0
}

// 4 ticks if not (HL), 8 ticks if (HL)
void CPU::or_a_r8()
{
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = R8::HL}); // 4
	pushToQueue({.type = CPUMicroOpType::OR_A_R8, .cycles = 0, .r8_src = r8});	   // 0
}

// 4 ticks if not (HL), 8 ticks if (HL)
void CPU::cp_a_r8()
{
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = R8::HL}); // 4
	pushToQueue({.type = CPUMicroOpType::CP_A_R8, .cycles = 0, .r8_src = r8});	   // 0
}
/**************************************/
/**              Block 3             **/
/**************************************/
// 8 ticks
void CPU::add_a_imm8()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});					// 4
	pushToQueue({.type = CPUMicroOpType::ADD_A_IMM8, .cycles = 0}); // 0
}

// 8 ticks
void CPU::adc_a_imm8()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});					// 4
	pushToQueue({.type = CPUMicroOpType::ADC_A_IMM8, .cycles = 0}); // 0
}

// 8 ticks
void CPU::sub_a_imm8()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});					// 4
	pushToQueue({.type = CPUMicroOpType::SUB_A_IMM8, .cycles = 0}); // 0
}

// 8 ticks
void CPU::sbc_a_imm8()
{
	std::cout << "sbc_a_imm8 not implemented" << std::endl;
	ctx.setRunning(false);
}

// 8 ticks
void CPU::and_a_imm8()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});					// 4
	pushToQueue({.type = CPUMicroOpType::AND_A_IMM8, .cycles = 0}); // 0
}

// 8 ticks
void CPU::xor_a_imm8()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});					// 4
	pushToQueue({.type = CPUMicroOpType::XOR_A_IMM8, .cycles = 0}); // 0
}

// 8 ticks
void CPU::or_a_imm8()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});				   // 4
	pushToQueue({.type = CPUMicroOpType::OR_A_IMM8, .cycles = 0}); // 0
}

// 8 ticks
void CPU::cp_a_imm8()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});				   // 4
	pushToQueue({.type = CPUMicroOpType::CP_A_IMM8, .cycles = 0}); // 0
}

// 8 ticks if cond false, 20 ticks if cond true
void CPU::ret_cond()
{
	COND cond = Registers::getCONDFromCode((opCode() & 0b00011000) >> 3);
	pushToQueue({.type = CPUMicroOpType::RET_CONDITIONAL, .cycles = 0, .cond = cond});
}

// 16 ticks
void CPU::ret()
{
	pushToQueue({CPUMicroOpType::READ_SP_LOW});		// 4
	pushToQueue({CPUMicroOpType::READ_SP_HIGH});	// 4
	pushToQueue({CPUMicroOpType::WRITE_TMP_TO_PC}); // 4
}

// 16 ticks
void CPU::reti()
{
	pushToQueue({CPUMicroOpType::READ_SP_LOW});		// 4
	pushToQueue({CPUMicroOpType::READ_SP_HIGH});	// 4
	pushToQueue({CPUMicroOpType::WRITE_TMP_TO_PC}); // 4
	pushToQueue({CPUMicroOpType::EI, 0});			// 0
}

// 12 ticks if cond false, 16 ticks if cond true
void CPU::jp_cond_imm16()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});  // 4
	pushToQueue({CPUMicroOpType::READ_IMM8_HIGH}); // 4
	COND cond = Registers::getCONDFromCode((opCode() & 0b00011000) >> 3);
	pushToQueue({.type = CPUMicroOpType::JP_CONDITIONAL, .cycles = 0, .cond = cond}); // 0 or 4
}

// 16 ticks
void CPU::jp_imm16()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});	// 4
	pushToQueue({CPUMicroOpType::READ_IMM8_HIGH});	// 4
	pushToQueue({CPUMicroOpType::WRITE_TMP_TO_PC}); // 4
}

// 4 ticks
void CPU::jp_hl()
{
	pushToQueue({CPUMicroOpType::JP_HL, 0});
}

// 12 ticks if cond false, 24 ticks if cond true
void CPU::call_cond_imm16()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});  // 4
	pushToQueue({CPUMicroOpType::READ_IMM8_HIGH}); // 4
	COND cond = Registers::getCONDFromCode((opCode() & 0b00011000) >> 3);
	pushToQueue({.type = CPUMicroOpType::CALL_CONDITIONAL, .cycles = 0, .cond = cond}); // 0 or 12
}

// 24 ticks
void CPU::call_imm16()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});		 // 4
	pushToQueue({CPUMicroOpType::READ_IMM8_HIGH});		 // 4
	pushToQueue({CPUMicroOpType::PUSH_SP_HIGH_FROM_PC}); // 4
	pushToQueue({CPUMicroOpType::PUSH_SP_LOW_FROM_PC});	 // 4
	pushToQueue({CPUMicroOpType::WRITE_TMP_TO_PC});		 // 4
}

// 16 ticks
void CPU::rst_tgt3()
{
	u8 tgt3 = (opCode() & 0b00111000) >> 3;
	pushToQueue({.type = CPUMicroOpType::READ_TGT3, .cycles = 0, .tgt3 = tgt3}); // 0
	pushToQueue({CPUMicroOpType::PUSH_SP_HIGH_FROM_PC});						 // 4
	pushToQueue({CPUMicroOpType::PUSH_SP_LOW_FROM_PC});							 // 4
	pushToQueue({CPUMicroOpType::WRITE_TMP_TO_PC});								 // 4
}

// 12 ticks
void CPU::pop_r16stk()
{
	R16_STK r16Stk = Registers::getR16StkFromCode((opCode() & 0b00110000) >> 4);
	pushToQueue({CPUMicroOpType::READ_SP_LOW});												   // 4
	pushToQueue({CPUMicroOpType::READ_SP_HIGH});											   // 4
	pushToQueue({.type = CPUMicroOpType::WRITE_TMP_TO_R16STK, .cycles = 0, .r16Stk = r16Stk}); // 0
}

// 16 ticks
void CPU::push_r16stk()
{
	R16_STK r16Stk = Registers::getR16StkFromCode((opCode() & 0b00110000) >> 4);
	pushToQueue({CPUMicroOpType::INTERNAL});
	pushToQueue({.type = CPUMicroOpType::PUSH_SP_HIGH_FROM_R16STK, .r16Stk = r16Stk});
	pushToQueue({.type = CPUMicroOpType::PUSH_SP_LOW_FROM_R16STK, .r16Stk = r16Stk});
}

// 8 ticks
void CPU::ldh_c_a()
{
	pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .cycles = 0, .r8_src = R8::C});
	pushToQueue({CPUMicroOpType::WRITE_A_TO_LDH_ADDR});
}

// 12 ticks
void CPU::ldh_imm8_a()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});
	pushToQueue({CPUMicroOpType::WRITE_A_TO_LDH_ADDR});
}

// 16 ticks
void CPU::ld_imm16_a()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});
	pushToQueue({CPUMicroOpType::READ_IMM8_HIGH});
	pushToQueue({CPUMicroOpType::WRITE_A_TO_TMP_ADDR});
}

// 8 ticks
void CPU::ldh_a_c()
{
	std::cout << "ldh_a_c not implemented" << std::endl;
	ctx.setRunning(false);
}

// 12 ticks
void CPU::ldh_a_imm8()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});		// 4
	pushToQueue({CPUMicroOpType::WRITE_LDH_ADDR_TO_A}); // 4
}

// 16 ticks
void CPU::ld_a_imm16()
{
	pushToQueue({CPUMicroOpType::READ_IMM8_LOW});								  // 4
	pushToQueue({CPUMicroOpType::READ_IMM8_HIGH});								  // 4
	pushToQueue({.type = CPUMicroOpType::WRITE_TMP_ADDR_TO_A, .r8_dest = R8::A}); // 4
}

// 16 ticks
void CPU::add_sp_imm8()
{
	std::cout << "add_sp_imm8 not implemented" << std::endl;
	ctx.setRunning(false);
}

// 12 ticks
void CPU::ld_hl_sp_imm8()
{
	std::cout << "ld_hl_sp_imm8 not implemented" << std::endl;
	ctx.setRunning(false);
}

// 8 ticks
void CPU::ld_sp_hl()
{
	std::cout << "ld_sp_hl not implemented" << std::endl;
	ctx.setRunning(false);
}

// 4 ticks
void CPU::di()
{
	pushToQueue({CPUMicroOpType::DI, 0}); // 0
}

// 4 ticks
void CPU::ei()
{
	pushToQueue({CPUMicroOpType::EI, 0}); // 0
}

/**************************************/
/**           $CB prefix             **/
/**************************************/
// 8 ticks if not (HL), 16 ticks if (HL)
void CPU::rlc_r8()
{
	std::cout << "rlc_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}

// 8 ticks if not (HL), 16 ticks if (HL)
void CPU::rrc_r8()
{
	std::cout << "rrc_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}

// 8 ticks if not (HL), 16 ticks if (HL)
void CPU::rl_r8()
{
	std::cout << "rl_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}

// 8 ticks if not (HL), 16 ticks if (HL)
void CPU::rr_r8()
{
	u8 b3 = (cbPrefixOpCode() & 0b00111000) >> 3;
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = R8::HL});	  // 4
	pushToQueue({.type = CPUMicroOpType::RR, .cycles = 0, .r8_dest = r8, .bit = b3}); // 4
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::WRITE_TMP_TO_R8, .r8_dest = R8::HL}); // 4
}

// 8 ticks if not (HL), 16 ticks if (HL)
void CPU::sla_r8()
{
	u8 b3 = (cbPrefixOpCode() & 0b00111000) >> 3;
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = R8::HL});	   // 4
	pushToQueue({.type = CPUMicroOpType::SLA, .cycles = 0, .r8_dest = r8, .bit = b3}); // 4
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::WRITE_TMP_TO_R8, .r8_dest = R8::HL}); // 4
}

// 8 ticks if not (HL), 16 ticks if (HL)
void CPU::sra_r8()
{
	std::cout << "sra_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}

// 8 ticks if not (HL), 16 ticks if (HL)
void CPU::swap_r8()
{
	u8 b3 = (cbPrefixOpCode() & 0b00111000) >> 3;
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = R8::HL});		// 4
	pushToQueue({.type = CPUMicroOpType::SWAP, .cycles = 0, .r8_dest = r8, .bit = b3}); // 4
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::WRITE_TMP_TO_R8, .r8_dest = R8::HL}); // 4
}

// 8 ticks if not (HL), 16 ticks if (HL)
void CPU::srl_r8()
{
	u8 b3 = (cbPrefixOpCode() & 0b00111000) >> 3;
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = R8::HL});	   // 4
	pushToQueue({.type = CPUMicroOpType::SRL, .cycles = 0, .r8_dest = r8, .bit = b3}); // 4
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::WRITE_TMP_TO_R8, .r8_dest = R8::HL}); // 4
}

// 8 ticks if not (HL), 12 ticks if (HL)
void CPU::bit_b3_r8()
{
	u8 b3 = (cbPrefixOpCode() & 0b00111000) >> 3;
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = R8::HL});		   // 4
	pushToQueue({.type = CPUMicroOpType::TEST_BIT, .cycles = 0, .r8_src = r8, .bit = b3}); // 0
}

// 8 ticks if not (HL), 16 ticks if (HL)
void CPU::res_b3_r8()
{
	u8 b3 = (cbPrefixOpCode() & 0b00111000) >> 3;
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::READ_TMP_FROM_R8, .r8_src = R8::HL});		   // 4
	pushToQueue({.type = CPUMicroOpType::RES_BIT, .cycles = 0, .r8_dest = r8, .bit = b3}); // 0
	if (r8 == R8::HL)
		pushToQueue({.type = CPUMicroOpType::WRITE_TMP_TO_R8, .r8_dest = R8::HL}); // 4
}

// 8 ticks if not (HL), 16 ticks if (HL)
void CPU::set_b3_r8()
{
	std::cout << "set_b3_r8 not implemented" << std::endl;
	ctx.setRunning(false);
}
