#pragma once

#include <Common.h>

class Context;
class CORE_API CPU
{
private:
	Context &ctx;
	u8 currentOpCode;
	u8 currentCBPrefixOpCode;

	bool ime = false;

public:
	CPU(Context &ctx);
	~CPU();

	u8 opCode() { return currentOpCode; }
	void setCurrentOpCode(u8 opCode) { currentOpCode = opCode; }
	u8 cbPrefixOpCode() { return currentCBPrefixOpCode; }
	void setCurrentCBPRefixOpCode(u8 opCode) { currentCBPrefixOpCode = opCode; }

	bool isIME() { return ime; }
	void setIME(bool ime) { this->ime = ime; }

	// Main entry points
	void runOp();

	// Block 0
	void nop();
	void ld_r16_imm16();
	void ld_r16mem_a();
	void ld_a_r16mem();
	void ld_imm16_sp();
	void inc_r16();
	void dec_r16();
	void add_hl_r16();
	void inc_r8();
	void dec_r8();
	void ld_r8_imm8();
	void rlca();
	void rrca();
	void rla();
	void rra();
	void daa();
	void cpl();
	void scf();
	void ccf();
	void jr_imm8();
	void jr_cond_imm8();
	void stop();
	// Block 1 : 8-bit reg to reg loads
	void ld_r8_r8();
	void halt();
	// Block 2 : 8-bit arithmetic
	void add_a_r8();
	void adc_a_r8();
	void sub_a_r8();
	void sbc_a_r8();
	void and_a_r8();
	void xor_a_r8();
	void or_a_r8();
	void cp_a_r8();
	// Block 3
	void add_a_imm8();
	void adc_a_imm8();
	void sub_a_imm8();
	void sbc_a_imm8();
	void and_a_imm8();
	void xor_a_imm8();
	void or_a_imm8();
	void cp_a_imm8();
	void ret_cond();
	void ret();
	void reti();
	void jp_cond_imm16();
	void jp_imm16();
	void jp_hl();
	void call_cond_imm16();
	void call_imm16();
	void rst_tgt3();
	void pop_r16stk();
	void push_r16stk();
	void prefix();
	void ldh_c_a();
	void ldh_imm8_a();
	void ld_imm16_a();
	void ldh_a_c();
	void ldh_a_imm8();
	void ld_a_imm16();
	void add_sp_imm8();
	void ld_hl_sp_imm8();
	void ld_sp_hl();
	void di();
	void ei();
	//$CB prefix
	void rlc_r8();
	void rrc_r8();
	void rl_r8();
	void rr_r8();
	void sla_r8();
	void sra_r8();
	void swap_r8();
	void srl_r8();
	void bit_b3_r8();
	void res_b3_r8();
	void set_b3_r8();
};
