#pragma once

#include <functional>
#include <queue>
#include <Common.h>
#include <Interrupts.h>

using CPUMicroOp = std::function<void()>;

class Context;
class CORE_API CPU
{
private:
	Context &ctx;
	Interrupts interrupts;
	u8 currentOpCode;
	u8 currentCBPrefixOpCode;

	// Scheduler, starts at cycle 0 because tick increments cycles in first line
	u64 cycles = 0;
	int currentTCycles = 0;
	std::queue<CPUMicroOp> queue = {};
	bool instructionJustFinished = false;

	void fetchDecodeOp();
	void executeMicroOps();

public:
	CPU(Context &ctx);
	~CPU();

	void tick();

	u8 getCurrentTCycles() { return currentTCycles; }
	void setCurrentTCycles(u8 currentTCycles) { this->currentTCycles = currentTCycles; }

	u64 getCycles() { return cycles; }
	void setCycles(u64 cycles) { this->cycles = cycles; }

	std::string opCodeToString();
	u8 opCode() { return currentOpCode; }
	void setCurrentOpCode(u8 opCode) { currentOpCode = opCode; }

	u8 cbPrefixOpCode() { return currentCBPrefixOpCode; }
	void setCurrentCBPRefixOpCode(u8 opCode) { currentCBPrefixOpCode = opCode; }

	Interrupts &getInterrupts() { return interrupts; }

	void runOp(u8 code);

	bool isInstructionJustFinished() { return instructionJustFinished; }
	void pushToQueue(const CPUMicroOp &op) { queue.push(op); }
	std::queue<CPUMicroOp> &getQueue() { return queue; }
	void clearQueue()
	{
		std::queue<CPUMicroOp> empty;
		std::swap(queue, empty);
	};

	/************************************************/
	/*              8-bit load instructions         */
	/************************************************/

	// 0x40 (B/B), 0x41 (B/C), 0x42 (B/D), 0x43 (B/E), 0x44 (B/H), 0x45 (B/L), 0x47 (B/A)
	// 0x48 (C/B), 0x49 (C/C), 0x4A (C/D), 0x4B (C/E), 0x4C (C/H), 0x4D (C/L), 0x4F (C/A)
	// 0x50 (D/B), 0x51 (D/C), 0x52 (D/D), 0x53 (D/E), 0x54 (D/H), 0x55 (D/L), 0x57 (D/A)
	// 0x58 (E/B), 0x59 (E/C), 0x5A (E/D), 0x5B (E/E), 0x5C (E/H), 0x5D (E/L), 0x5F (E/A)
	// 0x60 (H/B), 0x61 (H/C), 0x62 (H/D), 0x63 (H/E), 0x64 (H/H), 0x65 (H/L), 0x67 (H/A)
	// 0x68 (L/B), 0x69 (L/C), 0x6A (L/D), 0x6B (L/E), 0x6C (L/H), 0x6D (L/L), 0x6F (L/A)
	// 0x78 (A/B), 0x79 (A/C), 0x7A (A/D), 0x7B (A/E), 0x7C (A/H), 0x7D (A/L), 0x7F (A/A)
	void ld_r1_r2();
	// 0x06 (B), 0x0E (C), 0x16 (D), 0x1E (E), 0x26 (H), 0x2E (L), 0x3E (A)
	void ld_r_n();
	// 0x46 (B), 0x4E (C), 0x56 (D), 0x5E (E), 0x66 (H), 0x6E (L), 0x7E (A)
	void ld_r_hl();
	// 0x70 (B), 0x71 (C), 0x72 (D), 0x73 (E), 0x74 (H), 0x75 (L), 0x77 (A)
	void ld_hl_r();
	// 0x36
	void ld_hl_n();
	// 0x0A
	void ld_a_bc();
	// 0x1A
	void ld_a_de();
	// 0x02
	void ld_bc_a();
	// 0x12
	void ld_de_a();
	// 0xFA
	void ld_a_nn();
	// 0xEA
	void ld_nn_a();
	// 0xF2
	void ldh_a_c();
	// 0xE2
	void ldh_c_a();
	// 0xF0
	void ldh_a_n();
	// 0xE0
	void ldh_n_a();
	// 0x3A
	void ld_a_hld();
	// 0x32
	void ld_hld_a();
	// 0x2A
	void ld_a_hli();
	// 0x22
	void ld_hli_a();
	// 16-bit load instructions
	// 0x01 (BC), 0x11 (DE), 0x21 (HL), 0x31 (SP)
	void ld_rr_nn();
	// 0x08
	void ld_nn_sp();
	// 0xF9
	void ld_sp_hl();
	// 0xC5 (BC), 0xD5 (DE), 0xE5 (HL), 0xF5 (SP)
	void push_rr();
	// 0xC1 (BC), 0xD1 (DE), 0xE1 (HL), 0xF1 (SP)
	void pop_rr();
	// 0xF8
	void ld_hl_sp_e();
	/************************************************/
	/* 8-bit arithmetic and logical instructions    */
	/************************************************/

	// 0x80 (B), 0x81 (C), 0x82 (D), 0x83 (E), 0x84 (H), 0x85 (L), 0x87 (A)
	void add_r();
	// 0x86
	void add_hl();
	// 0xC6
	void add_n();
	// 0x88 (B), 0x89 (C), 0x8A (D), 0x8B (E), 0x8C (H), 0x8D (L), 0x8F (A)
	void adc_r();
	// 0x8E
	void adc_hl();
	// 0xCE
	void adc_n();
	// 0x90 (B), 0x91 (C), 0x92 (D), 0x93 (E), 0x94 (H), 0x95 (L), 0x97 (A)
	void sub_r();
	// 0x96
	void sub_hl();
	// 0xD6
	void sub_n();
	// 0x98 (B), 0x99 (C), 0x9A (D), 0x9B (E), 0x9C (H), 0x9D (L), 0x9F (A)
	void sbc_r();
	// 0x9E
	void sbc_hl();
	// 0xDE
	void sbc_n();
	// 0xB8 (B), 0xB9 (C), 0xBA (D), 0xBB (E), 0xBC (H), 0xBD (L), 0xBF (A)
	void cp_r();
	// 0xBE
	void cp_hl();
	// 0xFE
	void cp_n();
	// 0x04 (B), 0x0C (C), 0x14 (D), 0x1C (E), 0x24 (H), 0x2C (L), 0x3C (A)
	void inc_r();
	// 0x34
	void inc_hl();
	// 0x06 (B), 0x0E (C), 0x16 (D), 0x1E (E), 0x26 (H), 0x2E (L), 0x3E (A)
	void dec_r();
	// 0x36
	void dec_hl();
	// 0xA0 (B), 0xA1 (C), 0xA2 (D), 0xA3 (E), 0xA4 (H), 0xA5 (L), 0xA7 (A)
	void and_r();
	// 0xA6
	void and_hl();
	// 0xE6
	void and_n();
	// 0xB0 (B), 0xB1 (C), 0xB2 (D), 0xB3 (E), 0xB4 (H), 0xB5 (L), 0xB7 (A)
	void or_r();
	// 0xB6
	void or_hl();
	// 0xF6
	void or_n();
	// 0xA8 (B), 0xA9 (C), 0xAA (D), 0xAB (E), 0xAC (H), 0xAD (L), 0xAF (A)
	void xor_r();
	// 0xAE
	void xor_hl();
	// 0xEE
	void xor_n();
	// 0x3F
	void ccf();
	// 0x37
	void scf();
	// 0x27
	void daa();
	// 0x2F
	void cpl();
	/************************************************/
	/*         16-bit arithmetic instructions       */
	/************************************************/

	// 0x03 (BC), 0x13 (DE), 0x23 (HL), 0x33 (SP)
	void inc_rr();
	// 0x0B (BC), 0x1B (DE), 0x2B (HL), 0x3B (SP)
	void dec_rr();
	// 0x09 (BC), 0x19 (DE), 0x29 (HL), 0x39 (SP)
	void add_hl_rr();
	// 0xE8
	void add_sp_e();
	/************************************************/
	/* Rotate, shift and bit operation instructions */
	/************************************************/

	// 0x07
	void rlca();
	// 0x0F
	void rrca();
	// 0x17
	void rla();
	// 0x1F
	void rra();
	// 0xCB00 (B), 0xCB01 (C), 0xCB02 (D), 0xCB03 (E), 0xCB04 (H), 0xCB05 (L), , 0xCB07 (A)
	void rlc_r();
	// 0xCB06
	void rlc_hl();
	// 0xCB08 (B), 0xCB09 (C), 0xCB0A (D), 0xCB0B (E), 0xCB0C (H), 0xCB0D (L), 0xCB0F (A)
	void rrc_r();
	// 0xCB0E
	void rrc_hl();
	// 0xCB10 (B), 0xCB11 (C), 0xCB12 (D), 0xCB13 (E), 0xCB14 (H), 0xCB15 (L), 0xCB17 (A)
	void rl_r();
	// 0xCB16
	void rl_hl();
	// 0xCB18 (B), 0xCB19 (C), 0xCB1A (D), 0xCB1B (E), 0xCB1C (H), 0xCB1D (L), 0xCB1F (A)
	void rr_r();
	// 0xCB1E
	void rr_hl();
	// 0xCB20 (B), 0xCB21 (C), 0xCB22 (D), 0xCB23 (E), 0xCB24 (H), 0xCB25 (L), 0xCB27 (A)
	void sla_r();
	// 0xCB26
	void sla_hl();
	// 0xCB28 (B), 0xCB29 (C), 0xCB2A (D), 0xCB2B (E), 0xCB2C (H), 0xCB2D (L), 0xCB2F (A)
	void sra_r();
	// 0xCB2E
	void sra_hl();
	// 0xCB30 (B), 0xCB31 (C), 0xCB32 (D), 0xCB33 (E), 0xCB34 (H), 0xCB35 (L), 0xCB37 (A)
	void swap_r();
	// 0xCB36
	void swap_hl();
	// 0xCB38 (B), 0xCB39 (C), 0xCB3A (D), 0xCB3B (E), 0xCB3C (H), 0xCB3D (L), 0xCB3F (A)
	void srl_r();
	// 0xCB3E
	void srl_hl();
	// 0xCB40 (0 / B),0xCB41 (0 / C), 0xCB42 (0 / D), 0xCB43 (0 / E), 0xCB44 (0 / H), 0xCB45 (0 / L), 0xCB47 (0 / A)
	// 0xCB48 (1 / B),0xCB49 (1 / C), 0xCB4A (1 / D), 0xCB4B (1 / E), 0xCB4C (1 / H), 0xCB4D (1 / L), 0xCB4F (1 / A)
	// 0xCB50 (2 / B),0xCB51 (2 / C), 0xCB52 (2 / D), 0xCB53 (2 / E), 0xCB54 (2 / H), 0xCB55 (2 / L), 0xCB57 (2 / A)
	// 0xCB58 (3 / B),0xCB59 (3 / C), 0xCB5A (3 / D), 0xCB5B (3 / E), 0xCB5C (3 / H), 0xCB5D (3 / L), 0xCB5F (3 / A)
	// 0xCB60 (4 / B),0xCB61 (4 / C), 0xCB62 (4 / D), 0xCB63 (4 / E), 0xCB64 (4 / H), 0xCB65 (4 / L), 0xCB67 (4 / A)
	// 0xCB68 (5 / B),0xCB69 (5 / C), 0xCB6A (5 / D), 0xCB6B (5 / E), 0xCB6C (5 / H), 0xCB6D (5 / L), 0xCB6F (5 / A)
	// 0xCB70 (6 / B),0xCB71 (6 / C), 0xCB72 (6 / D), 0xCB73 (6 / E), 0xCB74 (6 / H), 0xCB75 (6 / L), 0xCB77 (6 / A)
	// 0xCB78 (7 / B),0xCB79 (7 / C), 0xCB7A (7 / D), 0xCB7B (7 / E), 0xCB7C (7 / H), 0xCB7D (7 / L), 0xCB7F (7 / A)
	void bit_b_r();
	// 0xCB46 (0), 0xCB4E (1), 0xCB56 (2), 0xCB5E (3), 0xCB66 (4), 0xCB6E (5), 0xCB76 (6), 0xCB7E (7)
	void bit_b_hl();
	// 0xCB80 (0 / B),0xCB81 (0 / C), 0xCB82 (0 / D), 0xCB83 (0 / E), 0xCB84 (0 / H), 0xCB85 (0 / L), 0xCB87 (0 / A)
	// 0xCB88 (1 / B),0xCB89 (1 / C), 0xCB8A (1 / D), 0xCB8B (1 / E), 0xCB8C (1 / H), 0xCB8D (1 / L), 0xCB8F (1 / A)
	// 0xCB90 (2 / B),0xCB91 (2 / C), 0xCB92 (2 / D), 0xCB93 (2 / E), 0xCB94 (2 / H), 0xCB95 (2 / L), 0xCB97 (2 / A)
	// 0xCB98 (3 / B),0xCB99 (3 / C), 0xCB9A (3 / D), 0xCB9B (3 / E), 0xCB9C (3 / H), 0xCB9D (3 / L), 0xCB9F (3 / A)
	// 0xCBA0 (4 / B),0xCBA1 (4 / C), 0xCBA2 (4 / D), 0xCBA3 (4 / E), 0xCBA4 (4 / H), 0xCBA5 (4 / L), 0xCBA7 (4 / A)
	// 0xCBA8 (5 / B),0xCBA9 (5 / C), 0xCBAA (5 / D), 0xCBAB (5 / E), 0xCBAC (5 / H), 0xCBAD (5 / L), 0xCBAF (5 / A)
	// 0xCBB0 (6 / B),0xCBB1 (6 / C), 0xCBB2 (6 / D), 0xCBB3 (6 / E), 0xCBB4 (6 / H), 0xCBB5 (6 / L), 0xCBB7 (6 / A)
	// 0xCBB8 (7 / B),0xCBB9 (7 / C), 0xCBBA (7 / D), 0xCBBB (7 / E), 0xCBBC (7 / H), 0xCBBD (7 / L), 0xCBBF (7 / A)
	void res_b_r();
	// 0xCB86 (0), 0xCB8E (1), 0xCB96 (2), 0xCB9E (3), 0xCBA6 (4), 0xCBAE (5), 0xCBB6 (6), 0xCBBE (7)
	void res_b_hl();
	// 0xCBC0 (0 / B),0xCBC1 (0 / C), 0xCBC2 (0 / D), 0xCBC3 (0 / E), 0xCBC4 (0 / H), 0xCBC5 (0 / L), 0xCBC7 (0 / A)
	// 0xCBC8 (1 / B),0xCBC9 (1 / C), 0xCBCA (1 / D), 0xCBCB (1 / E), 0xCBCC (1 / H), 0xCBCD (1 / L), 0xCBCF (1 / A)
	// 0xCBD0 (2 / B),0xCBD1 (2 / C), 0xCBD2 (2 / D), 0xCBD3 (2 / E), 0xCBD4 (2 / H), 0xCBD5 (2 / L), 0xCBD7 (2 / A)
	// 0xCBD8 (3 / B),0xCBD9 (3 / C), 0xCBDA (3 / D), 0xCBDB (3 / E), 0xCBDC (3 / H), 0xCBDD (3 / L), 0xCBDF (3 / A)
	// 0xCBE0 (4 / B),0xCBE1 (4 / C), 0xCBE2 (4 / D), 0xCBE3 (4 / E), 0xCBE4 (4 / H), 0xCBE5 (4 / L), 0xCBE7 (4 / A)
	// 0xCBE8 (5 / B),0xCBE9 (5 / C), 0xCBEA (5 / D), 0xCBEB (5 / E), 0xCBEC (5 / H), 0xCBED (5 / L), 0xCBEF (5 / A)
	// 0xCBF0 (6 / B),0xCBF1 (6 / C), 0xCBF2 (6 / D), 0xCBF3 (6 / E), 0xCBF4 (6 / H), 0xCBF5 (6 / L), 0xCBF7 (6 / A)
	// 0xCBF8 (7 / B),0xCBF9 (7 / C), 0xCBFA (7 / D), 0xCBFB (7 / E), 0xCBFC (7 / H), 0xCBFD (7 / L), 0xCBFF (7 / A)
	void set_b_r();
	// 0xCBC6 (0), 0xCBCE (1), 0xCBD6 (2), 0xCBDE (3), 0xCBE6 (4), 0xCBEE (5), 0xCBF6 (6), 0xCBFE (7)
	void set_b_hl();
	/************************************************/
	/*          Control flow instructions           */
	/************************************************/
	// 0xC3
	void jp_nn();
	// 0xE9
	void jp_hl();
	// 0xC2 (NZ), 0xCA (Z), 0xD2 (NC), 0xDA (C)
	void jp_cc_nn();
	// 0x18
	void jr_e();
	// 0x20 (NZ), 0x28 (Z), 0x30 (NC), 0x38 (C)
	void jr_cc_e();
	// 0xCD
	void call_nn();
	// 0xC4 (NZ), 0xCC (Z), 0xD4 (NC), 0xDC (C)
	void call_cc_nn();
	// 0xC9
	void ret();
	// 0xC0 (NZ), 0xC8 (Z), 0xD0 (NC), 0xD8 (C)
	void ret_cc();
	// 0xD9
	void reti();
	// 0xC7 (00H), 0xCF (08H), 0xD7 (10H), 0xDF (18H), 0xE7 (20H), 0xEF (28H), 0xF7 (30H), 0xFF (38H)
	void rst_n();
	/************************************************/
	/*          Miscellaneous instructions          */
	/************************************************/
	// 0x76
	void halt();
	// 0x10
	void stop();
	// 0xF3
	void di();
	//	0xFB
	void ei();
	// 0x00
	void nop();
};
