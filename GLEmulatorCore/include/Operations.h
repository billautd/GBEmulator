#pragma once

#include "Common.h"

class Operations
{
public:
	static void runOp();
	//Block 0
	static void nop();
	static void ld_r16_imm16();
	static void ld_r16mem_a();
	static void ld_a_r16mem();
	static void ld_imm16_sp();
	static void inc_r16();
	static void dec_r16();
	static void add_hl_r16();
	static void inc_r8();
	static void dec_r8();
	static void ld_r8_imm8();
	static void rlca();
	static void rrca();
	static void rla();
	static void rra();
	static void daa();
	static void cpl();
	static void scf();
	static void ccf();
	static void jr_imm8();
	static void jr_cond_imm8();
	static void stop();
	//Block 1 : 8-bit reg to reg loads
	static void ld_r8_r8();
	static void halt();
	//Block 2 : 8-bit arithmetic
	static void add_a_r8();
	static void adc_a_r8();
	static void sub_a_r8();
	static void sbc_a_r8();
	static void and_a_r8();
	static void xor_a_r8();
	static void or_a_r8();
	static void cp_a_r8();
	//Block 3
	static void add_a_imm8();
	static void adc_a_imm8();
	static void sub_a_imm8();
	static void sbc_a_imm8();
	static void and_a_imm8();
	static void xor_a_imm8();
	static void or_a_imm8();
	static void cp_a_imm8();
	static void ret_cond();
	static void ret();
	static void reti();
	static void jp_cond_imm16();
	static void jp_imm16();
	static void jp_hl();
	static void call_cond_imm16();
	static void call_imm16();
	static void rst_tgt3();
	static void pop_r16stk();
	static void push_r16stk();
	static void prefix();
	static void ldh_c_a();
	static void ldh_imm8_a();
	static void ld_imm16_a();
	static void ldh_a_c();
	static void ldh_a_imm8();
	static void ld_a_imm16();
	static void add_sp_imm8();
	static void ld_hl_sp_imm8();
	static void ld_sp_hl();
	static void di();
	static void ei();
	//$CB prefix
	static void rlc_r8();
	static void rrc_r8();
	static void rl_r8();
	static void rr_r8();
	static void sla_r8();
	static void sra_r8();
	static void swap_r8();
	static void srl_r8();
	static void bit_b3_r8();
	static void res_b3_r8();
	static void set_b3_r8();
};

