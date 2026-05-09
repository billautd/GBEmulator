#include <CPU.h>
#include <Context.h>

#define CPU_DEBUG false

CPU::CPU(Context &ctx) : ctx(ctx), interrupts(Interrupts(ctx))
{
}

CPU::~CPU()
{
}

void CPU::tick()
{
	// Stall T-cycles for each M-cycle
	// Each instruction runs on cycles multiple of 4
	if (currentTCycles != 0)
	{
		cycles++;
		currentTCycles = (currentTCycles + 1) % 4;
		return;
	}

	// If no scheduled op, fetch and decode next op
	if (queue.empty())
		fetchDecodeOp();
	// If scheduled op, run it
	else
		executeMicroOps();

	// Manage interrupts
	if (instructionJustFinished)
		interrupts.handle();

	cycles++;
	currentTCycles = (currentTCycles + 1) % 4;
}

void CPU::fetchDecodeOp()
{
	instructionJustFinished = false;

	// If queue empty, scheduling next CPU operation
	// Each instruction in queue = 4 T-Cycles = 1 M-Cycle
	setCurrentOpCode(ctx.mem().readMem(ctx.regs().pc++));
	if (currentOpCode == 0xCB)
	{
		setCurrentCBPRefixOpCode(ctx.mem().readMem(ctx.regs().pc++));
		// Simulate 8 T-cycles for CB prefix
		pushToQueue([]() { /*Internal*/ });
	}
#if CPU_DEBUG
	std::cout << std::format("Cycle {} - {} => {}\n", Common::toHexStr(cycles), Common::toHexStr(currentOpCode), ctx.regs().log());
#endif
	runOp(currentOpCode);
}

void CPU::executeMicroOps()
{
	// Pop next instruction in queue and run it, until CPU operation is fully processed (empty queue)
	CPUMicroOp microOp = queue.front();
	queue.pop();
	microOp();

	if (queue.empty())
	{

		instructionJustFinished = true;
	}
}

void CPU::runOp(u8 code)
{
	if (code == 0x00)
		nop();
	else if (code == 0x01 || code == 0x11 || code == 0x21 || code == 0x31)
		ld_rr_nn();
	else if (code == 0x02)
		ld_bc_a();
	else if (code == 0x12)
		ld_de_a();
	else if (code == 0x22)
		ld_hli_a();
	else if (code == 0x32)
		ld_hld_a();
	else if (code == 0x0A)
		ld_a_bc();
	else if (code == 0x1A)
		ld_a_de();
	else if (code == 0x2A)
		ld_a_hli();
	else if (code == 0x3A)
		ld_a_hld();
	else if (code == 0x08)
		ld_nn_sp();
	else if (code == 0x03 || code == 0x13 || code == 0x23 || code == 0x33)
		inc_rr();
	else if (code == 0x0B || code == 0x1B || code == 0x2B || code == 0x3B)
		dec_rr();
	else if (code == 0x09 || code == 0x19 || code == 0x29 || code == 0x39)
		add_hl_rr();
	else if (code == 0x04 || code == 0x0C || code == 0x14 || code == 0x1C || code == 0x24 || code == 0x2C || code == 0x3C)
		inc_r();
	else if (code == 0x34)
		inc_hl();
	else if (code == 0x05 || code == 0x0D || code == 0x15 || code == 0x1D || code == 0x25 || code == 0x2D || code == 0x3D)
		dec_r();
	else if (code == 0x35)
		dec_hl();
	else if (code == 0x06 || code == 0x0E || code == 0x16 || code == 0x1E || code == 0x26 || code == 0x2E || code == 0x3E)
		ld_r_n();
	else if (code == 0x36)
		ld_hl_n();
	else if (code == 0x07)
		rlca();
	else if (code == 0x0F)
		rrca();
	else if (code == 0x17)
		rla();
	else if (code == 0x1F)
		rra();
	else if (code == 0x27)
		daa();
	else if (code == 0x2F)
		cpl();
	else if (code == 0x37)
		scf();
	else if (code == 0x3F)
		ccf();
	else if (code == 0x18)
		jr_e();
	else if (code == 0x20 || code == 0x28 || code == 0x30 || code == 0x38)
		jr_cc_e();
	else if (code == 0x10)
		stop();
	else if (code == 0x40 || code == 0x41 || code == 0x42 || code == 0x43 || code == 0x44 || code == 0x45 || code == 0x47 ||
			 code == 0x48 || code == 0x49 || code == 0x4A || code == 0x4B || code == 0x4C || code == 0x4D || code == 0x4F ||
			 code == 0x50 || code == 0x51 || code == 0x52 || code == 0x53 || code == 0x54 || code == 0x55 || code == 0x57 ||
			 code == 0x58 || code == 0x59 || code == 0x5A || code == 0x5B || code == 0x5C || code == 0x5D || code == 0x5F ||
			 code == 0x60 || code == 0x61 || code == 0x62 || code == 0x63 || code == 0x64 || code == 0x65 || code == 0x67 ||
			 code == 0x68 || code == 0x69 || code == 0x6A || code == 0x6B || code == 0x6C || code == 0x6D || code == 0x6F ||
			 code == 0x78 || code == 0x79 || code == 0x7A || code == 0x7B || code == 0x7C || code == 0x7D || code == 0x7F)
		ld_r1_r2();
	else if (code == 0x46 || code == 0x4E || code == 0x56 || code == 0x5E || code == 0x66 || code == 0x6E || code == 0x7E)
		ld_r_hl();
	else if (code == 0x70 || code == 0x71 || code == 0x72 || code == 0x73 || code == 0x74 || code == 0x75 || code == 0x77)
		ld_hl_r();
	else if (code == 0x76)
		halt();
	else if (code == 0x80 || code == 0x81 || code == 0x82 || code == 0x83 || code == 0x84 || code == 0x85 || code == 0x87)
		add_r();
	else if (code == 0x86)
		add_hl();
	else if (code == 0x88 || code == 0x89 || code == 0x8A || code == 0x8B || code == 0x8C || code == 0x8D || code == 0x8F)
		adc_r();
	else if (code == 0x8E)
		adc_hl();
	else if (code == 0x90 || code == 0x91 || code == 0x92 || code == 0x93 || code == 0x94 || code == 0x95 || code == 0x97)
		sub_r();
	else if (code == 0x96)
		sub_hl();
	else if (code == 0x98 || code == 0x99 || code == 0x9A || code == 0x9B || code == 0x9C || code == 0x9D || code == 0x9F)
		sbc_r();
	else if (code == 0x9E)
		sbc_hl();
	else if (code == 0xA0 || code == 0xA1 || code == 0xA2 || code == 0xA3 || code == 0xA4 || code == 0xA5 || code == 0xA7)
		and_r();
	else if (code == 0xA6)
		and_hl();
	else if (code == 0xA8 || code == 0xA9 || code == 0xAA || code == 0xAB || code == 0xAC || code == 0xAD || code == 0xAF)
		xor_r();
	else if (code == 0xAE)
		xor_hl();
	else if (code == 0xB0 || code == 0xB1 || code == 0xB2 || code == 0xB3 || code == 0xB4 || code == 0xB5 || code == 0xB7)
		or_r();
	else if (code == 0xB6)
		or_hl();
	else if (code == 0xB8 || code == 0xB9 || code == 0xBA || code == 0xBB || code == 0xBC || code == 0xBD || code == 0xBF)
		cp_r();
	else if (code == 0xBE)
		cp_hl();
	else if (code == 0xC6)
		add_n();
	else if (code == 0xCE)
		adc_n();
	else if (code == 0xD6)
		sub_n();
	else if (code == 0xDE)
		sbc_n();
	else if (code == 0xE6)
		and_n();
	else if (code == 0xEE)
		xor_n();
	else if (code == 0xF6)
		or_n();
	else if (code == 0xFE)
		cp_n();
	else if (code == 0xC0 || code == 0xC8 || code == 0xD0 || code == 0xD8)
		ret_cc();
	else if (code == 0xC9)
		ret();
	else if (code == 0xD9)
		reti();
	else if (code == 0xC2 || code == 0xCA || code == 0xD2 || code == 0xDA)
		jp_cc_nn();
	else if (code == 0xC3)
		jp_nn();
	else if (code == 0xE9)
		jp_hl();
	else if (code == 0xC4 || code == 0xCC || code == 0xD4 || code == 0xDC)
		call_cc_nn();
	else if (code == 0xCD)
		call_nn();
	else if (code == 0xC7 || code == 0xCF || code == 0xD7 || code == 0xDF || code == 0xE7 || code == 0xEF || code == 0xF7 || code == 0xFF)
		rst_n();
	else if (code == 0xC1 || code == 0xD1 || code == 0xE1 || code == 0xF1)
		pop_rr();
	else if (code == 0xC5 || code == 0xD5 || code == 0xE5 || code == 0xF5)
		push_rr();
	else if (code == 0xE2)
		ldh_c_a();
	else if (code == 0xE0)
		ldh_n_a();
	else if (code == 0xEA)
		ld_nn_a();
	else if (code == 0xF2)
		ldh_a_c();
	else if (code == 0xF0)
		ldh_a_n();
	else if (code == 0xFA)
		ld_a_nn();
	else if (code == 0xE8)
		add_sp_e();
	else if (code == 0xF8)
		ld_hl_sp_e();
	else if (code == 0xF9)
		ld_sp_hl();
	else if (code == 0xF3)
		di();
	else if (code == 0xFB)
		ei();
	else if (code == 0xCB)
	{
		u8 cbCode = currentCBPrefixOpCode;
		if (cbCode == 0x00 || cbCode == 0x01 || cbCode == 0x02 || cbCode == 0x03 || cbCode == 0x04 || cbCode == 0x05 || cbCode == 0x07)
			rlc_r();
		else if (cbCode == 0x06)
			rlc_hl();
		else if (cbCode == 0x08 || cbCode == 0x09 || cbCode == 0x0A || cbCode == 0x0B || cbCode == 0x0C || cbCode == 0x0D || cbCode == 0x0F)
			rrc_r();
		else if (cbCode == 0x0E)
			rrc_hl();
		else if (cbCode == 0x10 || cbCode == 0x11 || cbCode == 0x12 || cbCode == 0x13 || cbCode == 0x14 || cbCode == 0x15 || cbCode == 0x17)
			rl_r();
		else if (cbCode == 0x16)
			rl_hl();
		else if (cbCode == 0x18 || cbCode == 0x19 || cbCode == 0x1A || cbCode == 0x1B || cbCode == 0x1C || cbCode == 0x1D || cbCode == 0x1F)
			rr_r();
		else if (cbCode == 0x1E)
			rr_hl();
		else if (cbCode == 0x20 || cbCode == 0x21 || cbCode == 0x22 || cbCode == 0x23 || cbCode == 0x24 || cbCode == 0x25 || cbCode == 0x27)
			sla_r();
		else if (cbCode == 0x26)
			sla_hl();
		else if (cbCode == 0x28 || cbCode == 0x29 || cbCode == 0x2A || cbCode == 0x2B || cbCode == 0x2C || cbCode == 0x2D || cbCode == 0x2F)
			sra_r();
		else if (cbCode == 0x2E)
			sra_hl();
		else if (cbCode == 0x30 || cbCode == 0x31 || cbCode == 0x32 || cbCode == 0x33 || cbCode == 0x34 || cbCode == 0x35 || cbCode == 0x37)
			swap_r();
		else if (cbCode == 0x36)
			swap_hl();
		else if (cbCode == 0x38 || cbCode == 0x39 || cbCode == 0x3A || cbCode == 0x3B || cbCode == 0x3C || cbCode == 0x3D || cbCode == 0x3F)
			srl_r();
		else if (cbCode == 0x3E)
			srl_hl();
		else if (cbCode == 0x40 || cbCode == 0x41 || cbCode == 0x42 || cbCode == 0x43 || cbCode == 0x44 || cbCode == 0x45 || cbCode == 0x47 ||
				 cbCode == 0x48 || cbCode == 0x49 || cbCode == 0x4A || cbCode == 0x4B || cbCode == 0x4C || cbCode == 0x4D || cbCode == 0x4F ||
				 cbCode == 0x50 || cbCode == 0x51 || cbCode == 0x52 || cbCode == 0x53 || cbCode == 0x54 || cbCode == 0x55 || cbCode == 0x57 ||
				 cbCode == 0x58 || cbCode == 0x59 || cbCode == 0x5A || cbCode == 0x5B || cbCode == 0x5C || cbCode == 0x5D || cbCode == 0x5F ||
				 cbCode == 0x60 || cbCode == 0x61 || cbCode == 0x62 || cbCode == 0x63 || cbCode == 0x64 || cbCode == 0x65 || cbCode == 0x67 ||
				 cbCode == 0x68 || cbCode == 0x69 || cbCode == 0x6A || cbCode == 0x6B || cbCode == 0x6C || cbCode == 0x6D || cbCode == 0x6F ||
				 cbCode == 0x70 || cbCode == 0x71 || cbCode == 0x72 || cbCode == 0x73 || cbCode == 0x74 || cbCode == 0x75 || cbCode == 0x77 ||
				 cbCode == 0x78 || cbCode == 0x79 || cbCode == 0x7A || cbCode == 0x7B || cbCode == 0x7C || cbCode == 0x7D || cbCode == 0x7F)
			bit_b_r();
		else if (cbCode == 0x46 || cbCode == 0x4E || cbCode == 0x56 || cbCode == 0x5E || cbCode == 0x66 || cbCode == 0x6E || cbCode == 0x76 || cbCode == 0x7E)
			bit_b_hl();
		else if (cbCode == 0x80 || cbCode == 0x81 || cbCode == 0x82 || cbCode == 0x83 || cbCode == 0x84 || cbCode == 0x85 || cbCode == 0x87 ||
				 cbCode == 0x88 || cbCode == 0x89 || cbCode == 0x8A || cbCode == 0x8B || cbCode == 0x8C || cbCode == 0x8D || cbCode == 0x8F ||
				 cbCode == 0x90 || cbCode == 0x91 || cbCode == 0x92 || cbCode == 0x93 || cbCode == 0x94 || cbCode == 0x95 || cbCode == 0x97 ||
				 cbCode == 0x98 || cbCode == 0x99 || cbCode == 0x9A || cbCode == 0x9B || cbCode == 0x9C || cbCode == 0x9D || cbCode == 0x9F ||
				 cbCode == 0xA0 || cbCode == 0xA1 || cbCode == 0xA2 || cbCode == 0xA3 || cbCode == 0xA4 || cbCode == 0xA5 || cbCode == 0xA7 ||
				 cbCode == 0xA8 || cbCode == 0xA9 || cbCode == 0xAA || cbCode == 0xAB || cbCode == 0xAC || cbCode == 0xAD || cbCode == 0xAF ||
				 cbCode == 0xB0 || cbCode == 0xB1 || cbCode == 0xB2 || cbCode == 0xB3 || cbCode == 0xB4 || cbCode == 0xB5 || cbCode == 0xB7 ||
				 cbCode == 0xB8 || cbCode == 0xB9 || cbCode == 0xBA || cbCode == 0xBB || cbCode == 0xBC || cbCode == 0xBD || cbCode == 0xBF)
			res_b_r();
		else if (cbCode == 0x86 || cbCode == 0x8E || cbCode == 0x96 || cbCode == 0x9E || cbCode == 0xA6 || cbCode == 0xAE || cbCode == 0xB6 || cbCode == 0xBE)
			res_b_hl();
		else if (cbCode == 0xC0 || cbCode == 0xC1 || cbCode == 0xC2 || cbCode == 0xC3 || cbCode == 0xC4 || cbCode == 0xC5 || cbCode == 0xC7 ||
				 cbCode == 0xC8 || cbCode == 0xC9 || cbCode == 0xCA || cbCode == 0xCB || cbCode == 0xCC || cbCode == 0xCD || cbCode == 0xCF ||
				 cbCode == 0xD0 || cbCode == 0xD1 || cbCode == 0xD2 || cbCode == 0xD3 || cbCode == 0xD4 || cbCode == 0xD5 || cbCode == 0xD7 ||
				 cbCode == 0xD8 || cbCode == 0xD9 || cbCode == 0xDA || cbCode == 0xDB || cbCode == 0xDC || cbCode == 0xDD || cbCode == 0xDF ||
				 cbCode == 0xE0 || cbCode == 0xE1 || cbCode == 0xE2 || cbCode == 0xE3 || cbCode == 0xE4 || cbCode == 0xE5 || cbCode == 0xE7 ||
				 cbCode == 0xE8 || cbCode == 0xE9 || cbCode == 0xEA || cbCode == 0xEB || cbCode == 0xEC || cbCode == 0xED || cbCode == 0xEF ||
				 cbCode == 0xF0 || cbCode == 0xF1 || cbCode == 0xF2 || cbCode == 0xF3 || cbCode == 0xF4 || cbCode == 0xF5 || cbCode == 0xF7 ||
				 cbCode == 0xF8 || cbCode == 0xF9 || cbCode == 0xFA || cbCode == 0xFB || cbCode == 0xFC || cbCode == 0xFD || cbCode == 0xFF)
			set_b_r();
		else if (cbCode == 0xC6 || cbCode == 0xCE || cbCode == 0xD6 || cbCode == 0xDE || cbCode == 0xE6 || cbCode == 0xEE || cbCode == 0xF6 || cbCode == 0xFE)
			set_b_hl();
		else
			throw std::runtime_error(std::string("Op code " + Common::toHexStr(cbCode) + "with CB prefix not managed"));
	}
	else if (code == 0xD3 || code == 0xDB || code == 0xDD ||
			 code == 0xE3 || code == 0xE4 || code == 0xEB ||
			 code == 0xEC || code == 0xED || code == 0xF4 ||
			 code == 0xFC || code == 0xFD)
		throw std::runtime_error(std::string("Invalid op code " + Common::toHexStr(code) + " from PC " + Common::toHexStr(ctx.regs().pc)));
	else
		throw std::runtime_error(std::string("Op code " + Common::toHexStr(code) + " not managed from PC " + Common::toHexStr(ctx.regs().pc)));
}

/**************************************/
/**    8-bit load instructions       **/
/**************************************/
void CPU::nop()
{
	// Nothing
}

void CPU::ld_rr_nn()
{
	R16 r16 = Registers::getR16FromCode((opCode() & 0b00110000) >> 4);
	auto low = std::make_shared<u8>();
	auto high = std::make_shared<u8>();
	// Read low
	pushToQueue([&, r16, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	// Read high
	pushToQueue([&, r16, low, high]()
				{ *high = ctx.mem().readMem(ctx.regs().pc++);
				ctx.regs().setRegFromR16(r16, (*high << 8) | *low); });
}

void CPU::ld_bc_a()
{
	// Write a to mem
	pushToQueue([&]()
				{ ctx.mem().writeMem(ctx.regs().getPointerFromR16Mem(R16_MEM::BC), ctx.regs().a); });
}

void CPU::ld_de_a()
{
	// Write a to mem
	pushToQueue([&]()
				{ ctx.mem().writeMem(ctx.regs().getPointerFromR16Mem(R16_MEM::DE), ctx.regs().a); });
}

void CPU::ld_hli_a()
{
	// Write a to mem
	pushToQueue([&]()
				{ ctx.mem().writeMem(ctx.regs().getPointerFromR16Mem(R16_MEM::HLI), ctx.regs().a);
        		ctx.regs().updateHLMem(R16_MEM::HLI); });
}

void CPU::ld_hld_a()
{
	// Write a to mem
	pushToQueue([&]()
				{ ctx.mem().writeMem(ctx.regs().getPointerFromR16Mem(R16_MEM::HLD), ctx.regs().a);
        		ctx.regs().updateHLMem(R16_MEM::HLD); });
}

void CPU::ld_a_bc()
{
	// Write mem to a
	pushToQueue([&]()
				{ ctx.regs().a = ctx.mem().readMem(ctx.regs().getPointerFromR16Mem(R16_MEM::BC)); });
}

void CPU::ld_a_de()
{
	// Write mem to a
	pushToQueue([&]()
				{ ctx.regs().a = ctx.mem().readMem(ctx.regs().getPointerFromR16Mem(R16_MEM::DE)); });
}

void CPU::ld_a_hli()
{
	// Write mem to a
	pushToQueue([&]()
				{ ctx.regs().a = ctx.mem().readMem(ctx.regs().getPointerFromR16Mem(R16_MEM::HLI));
				ctx.regs().updateHLMem(R16_MEM::HLI); });
}

void CPU::ld_a_hld()
{
	// Write mem to a
	pushToQueue([&]()
				{ ctx.regs().a = ctx.mem().readMem(ctx.regs().getPointerFromR16Mem(R16_MEM::HLD));
				ctx.regs().updateHLMem(R16_MEM::HLD); });
}

void CPU::ld_nn_sp()
{
	auto low = std::make_shared<u8>();
	auto high = std::make_shared<u8>();
	// Read low
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	// Read high
	pushToQueue([&, high]()
				{ *high = ctx.mem().readMem(ctx.regs().pc++); });
	// Write low to SP
	pushToQueue([&, low, high]()
				{ u16 addr = (*high << 8) | *low;
					ctx.mem().writeMem(addr, ctx.regs().sp & 0xFF); });
	// Write high to SP
	pushToQueue([&, low, high]()
				{ u16 addr = (*high << 8) | *low;
					addr++;
					ctx.mem().writeMem(addr, ctx.regs().sp >> 8); });
}

void CPU::inc_rr()
{
	// Update RR
	pushToQueue([&]()
				{ R16 r16 = Registers::getR16FromCode((opCode() & 0b00110000) >> 4);
				u16 newValue = ctx.regs().getFromR16(r16) + 1;
       			ctx.regs().setRegFromR16(r16, newValue); });
}

void CPU::dec_rr()
{
	// Update RR
	pushToQueue([&]()
				{ R16 r16 = Registers::getR16FromCode((opCode() & 0b00110000) >> 4);
			u16 newValue = ctx.regs().getFromR16(r16) - 1;
        	ctx.regs().setRegFromR16(r16, newValue); });
}

void CPU::add_hl_rr()
{
	// Update (HL)
	pushToQueue([&]()
				{ R16 r16 = Registers::getR16FromCode((opCode() & 0b00110000) >> 4);
        u16 r16Val = ctx.regs().getFromR16(r16);
        u16 hlVal = ctx.regs().getFromR16(R16::HL);
        u32 newVal32 = r16Val + hlVal;
        u16 newVal16 = (u16)newVal32;
        ctx.regs().setRegFromR16(R16::HL, newVal16);
        ctx.regs().setFlags(-1, 0, ((hlVal & 0x0FFF) + (r16Val & 0x0FFF)) > 0x0FFF, newVal32 > 0xFFFF); });
}

void CPU::inc_r()
{
	// Increment R8 directly
	R8 r8 = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
	u8 r8Value = ctx.regs().getFromR8(r8);
	u8 newValue = r8Value + 1;
	ctx.regs().setRegFromR8(r8, newValue);
	ctx.regs().setFlags(newValue == 0, 0, (r8Value & 0xF) == 0xF, -1);
}

void CPU::inc_hl()
{
	auto low = std::make_shared<u8>();
	// Read value at address
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL)); });
	// Write new value
	pushToQueue([&, low]()
				{ u8 newValue = *low + 1;
			ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), newValue);
			ctx.regs().setFlags(newValue == 0, 0, (*low & 0xF) == 0xF, -1); });
}

void CPU::dec_r()
{
	// Decrement R8 directly
	R8 r8 = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
	u8 r8Value = ctx.regs().getFromR8(r8);
	u8 newValue = r8Value - 1;
	ctx.regs().setRegFromR8(r8, newValue);
	ctx.regs().setFlags(newValue == 0, 1, (r8Value & 0xF) == 0, -1);
}

void CPU::dec_hl()
{
	auto low = std::make_shared<u8>();
	// Read value at address
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL)); });
	// Write new value
	pushToQueue([&, low]()
				{ u8 newValue = *low - 1;
			ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), newValue);
			ctx.regs().setFlags(newValue == 0, 1, (*low & 0xF) == 0, -1); });
}

void CPU::ld_r_n()
{
	// Write new value
	pushToQueue([&]()
				{ u8 imm8 = ctx.mem().readMem(ctx.regs().pc++);
				R8 r8 = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
				ctx.regs().setRegFromR8(r8, imm8); });
}

void CPU::ld_hl_n()
{
	auto low = std::make_shared<u8>();
	// Read value at address
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	// Write new value
	pushToQueue([&, low]()
				{ ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), *low); });
}

void CPU::rlca()
{
	// Do directly
	u8 r8Value = ctx.regs().a;
	bool b7 = Common::getBit(r8Value, 7);
	r8Value = (r8Value << 1 | b7);
	ctx.regs().a = r8Value;
	ctx.regs().setFlags(0, 0, 0, b7);
}

void CPU::rrca()
{
	// Do directly
	u8 r8Value = ctx.regs().a;
	bool b0 = Common::getBit(r8Value, 0);
	r8Value = (r8Value >> 1 | (b0 << 7));
	ctx.regs().a = r8Value;
	ctx.regs().setFlags(0, 0, 0, b0);
}

void CPU::rla()
{
	// Do directly
	u8 r8Value = ctx.regs().a;
	bool b7 = Common::getBit(r8Value, 7);
	bool carry = ctx.regs().getCFlag();
	r8Value = (r8Value << 1 | carry);
	ctx.regs().a = r8Value;
	ctx.regs().setFlags(0, 0, 0, b7);
}

void CPU::rra()
{
	// Do directly
	u8 r8Value = ctx.regs().a;
	bool b0 = Common::getBit(r8Value, 0);
	bool carry = ctx.regs().getCFlag();
	r8Value = (r8Value >> 1 | (carry << 7));
	ctx.regs().a = r8Value;
	ctx.regs().setFlags(0, 0, 0, b0);
}

void CPU::daa()
{
	// Do directly
	u8 r8Value = ctx.regs().a;
	bool z = ctx.regs().getZFlag();
	bool n = ctx.regs().getNFlag();
	bool h = ctx.regs().getHFlag();
	bool c = ctx.regs().getCFlag();

	bool carry = false;
	u8 tmp = 0;
	if (h || (!n && (r8Value & 0xF) > 0x09))
		tmp = 6;
	if (c || (!n && r8Value > 0x99))
	{
		tmp |= 0x60;
		carry = true;
	}

	u8 newValue = r8Value + (n ? -tmp : tmp);
	ctx.regs().a = newValue;
	ctx.regs().setFlags(newValue == 0, -1, 0, carry);
}

void CPU::cpl()
{
	// Do directly
	ctx.regs().a = ~ctx.regs().a;
	ctx.regs().setFlags(-1, 1, 1, -1);
}

void CPU::scf()
{
	// Do directly
	ctx.regs().setFlags(-1, 0, 0, 1);
}

void CPU::ccf()
{
	// Do directly
	bool carry = ctx.regs().getCFlag();
	ctx.regs().setFlags(-1, 0, 0, !carry);
}

void CPU::jr_e()
{
	auto low = std::make_shared<u8>();
	// Read value at address
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	// Jump
	pushToQueue([&, low]()
				{ ctx.regs().pc += (i8)*low; });
}

void CPU::jr_cc_e()
{
	COND cond = Registers::getCONDFromCode((opCode() & 0b00011000) >> 3);
	auto low = std::make_shared<u8>();
	// Read value at address
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	if (ctx.regs().checkCOND(cond))
		// If cond true, jump to signed value
		pushToQueue([&, low]()
					{ ctx.regs().pc += (i8)*low; });
}

void CPU::stop()
{
	std::cout << "stop not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::ld_r1_r2()
{
	// Load new value directly
	R8 r8_src = Registers::getR8FromCode(opCode() & 0b111);
	R8 r8_dest = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
	u8 newValue = ctx.regs().getFromR8(r8_src);
	ctx.regs().setRegFromR8(r8_dest, newValue);
}

void CPU::ld_r_hl()
{
	// Load new value from (HL)
	pushToQueue([&]()
				{ R8 r8_dest = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
					u8 newValue = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
					ctx.regs().setRegFromR8(r8_dest, newValue); });
}

void CPU::ld_hl_r()
{
	// Load new value to (HL)
	pushToQueue([&]()
				{ R8 r8_src = Registers::getR8FromCode(opCode() & 0b111);
					u8 newValue = ctx.regs().getFromR8(r8_src);
					ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), newValue); });
}

void CPU::halt()
{
	std::cout << "halt not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::add_r()
{
	// Update A directly
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	u8 previousAValue = ctx.regs().a;
	u8 r8Value = ctx.regs().getFromR8(r8);
	u16 newValue16 = previousAValue + r8Value;
	u8 newValue8 = (u8)newValue16;
	ctx.regs().a = newValue8;
	ctx.regs().setFlags(newValue8 == 0, 0, ((previousAValue & 0xF) + (r8Value & 0xF)) > 0xF, newValue16 > 0xFF);
}

void CPU::add_hl()
{
	// Update (HL)
	pushToQueue([&]()
				{ u8 previousAValue = ctx.regs().a;
			R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
       		u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
       		u16 newValue16 = previousAValue + r8Value;
       		u8 newValue8 = (u8)newValue16;
        	ctx.regs().a = newValue8;
        	ctx.regs().setFlags(newValue8 == 0, 0, ((previousAValue & 0xF) + (r8Value & 0xF)) > 0xF, newValue16 > 0xFF); });
}

void CPU::adc_r()
{
	// Update A directly
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	u8 previousAValue = ctx.regs().a;
	u8 r8Value = ctx.regs().getFromR8(r8);
	bool carry = ctx.regs().getCFlag();
	u16 newValue16 = previousAValue + r8Value + carry;
	u8 newValue8 = (u8)newValue16;
	ctx.regs().a = newValue8;
	ctx.regs().setFlags(newValue8 == 0, 0, ((previousAValue & 0xF) + (r8Value & 0xF) + carry) > 0xF, newValue16 > 0xFF);
}

void CPU::adc_hl()
{
	// Update (HL)
	pushToQueue([&]()
				{ 	u8 previousAValue = ctx.regs().a;
				R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
				u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
				bool carry = ctx.regs().getCFlag();
				u16 newValue16 = previousAValue + r8Value + carry;
				u8 newValue8 = (u8)newValue16;
				ctx.regs().a = newValue8;
				ctx.regs().setFlags(newValue8 == 0, 0, ((previousAValue & 0xF) + (r8Value & 0xF) + carry) > 0xF, newValue16 > 0xFF); });
}

void CPU::sub_r()
{
	// Update A directly
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	u8 previousAValue = ctx.regs().a;
	u8 r8Value = ctx.regs().getFromR8(r8);
	u8 newValue8 = previousAValue - r8Value;
	ctx.regs().a = newValue8;
	ctx.regs().setFlags(newValue8 == 0, 1, ((int)(previousAValue & 0xF) - (int)(r8Value & 0xF)) < 0, ((int)previousAValue - (int)r8Value) < 0);
}

void CPU::sub_hl()
{
	// Update (HL)
	pushToQueue([&]()
				{ R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
				u8 previousAValue = ctx.regs().a;
				u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
				u8 newValue8 = previousAValue - r8Value;
				ctx.regs().a = newValue8;
				ctx.regs().setFlags(newValue8 == 0, 1, ((int)(previousAValue & 0xF) - (int)(r8Value & 0xF)) < 0, ((int)previousAValue - (int)r8Value) < 0); });
}

void CPU::sbc_r()
{
	// Update A directly
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	u8 previousAValue = ctx.regs().a;
	u8 r8Value = ctx.regs().getFromR8(r8);
	bool carry = ctx.regs().getCFlag();
	u8 newValue8 = previousAValue - r8Value - carry;
	ctx.regs().a = newValue8;
	ctx.regs().setFlags(newValue8 == 0, 1, ((int)(previousAValue & 0xF) - (int)(r8Value & 0xF) - carry) < 0, ((int)previousAValue - (int)r8Value - carry) < 0);
}

void CPU::sbc_hl()
{
	// Update (HL)
	pushToQueue([&]()
				{ R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
				u8 previousAValue = ctx.regs().a;
				u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
				bool carry = ctx.regs().getCFlag();
				u8 newValue8 = previousAValue - r8Value - carry;
				ctx.regs().a = newValue8;
				ctx.regs().setFlags(newValue8 == 0, 1, ((int)(previousAValue & 0xF) - (int)(r8Value & 0xF) - carry) < 0, ((int)previousAValue - (int)r8Value - carry) < 0); });
}

void CPU::and_r()
{
	// Update A directly
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	u8 newValue = ctx.regs().a & r8Value;
	ctx.regs().a = newValue;
	ctx.regs().setFlags(newValue == 0, 0, 1, 0);
}

void CPU::and_hl()
{
	// Update (HL)
	pushToQueue([&]()
				{ R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
			u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
			u8 newValue = ctx.regs().a & r8Value;
			ctx.regs().a = newValue;
			ctx.regs().setFlags(newValue == 0, 0, 1, 0); });
}

void CPU::xor_r()
{
	// Update A directly
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	u8 newValue = ctx.regs().a ^ r8Value;
	ctx.regs().a = newValue;
	ctx.regs().setFlags(newValue == 0, 0, 0, 0);
}

void CPU::xor_hl()
{
	// Update (HL)
	pushToQueue([&]()
				{ R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
			u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
			u8 newValue = ctx.regs().a ^ r8Value;
			ctx.regs().a = newValue;
			ctx.regs().setFlags(newValue == 0, 0, 0, 0); });
}

void CPU::or_r()
{
	// Update A directly
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	u8 newValue = ctx.regs().a | r8Value;
	ctx.regs().a = newValue;
	ctx.regs().setFlags(newValue == 0, 0, 0, 0);
}

void CPU::or_hl()
{
	// Update (HL)
	pushToQueue([&]()
				{ R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
			u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
			u8 newValue = ctx.regs().a | r8Value;
			ctx.regs().a = newValue;
			ctx.regs().setFlags(newValue == 0, 0, 0, 0); });
}

void CPU::cp_r()
{
	// Update A directly
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	u8 a = ctx.regs().a;
	ctx.regs().setFlags((a - r8Value) == 0, 1, (a & 0xF) < (r8Value & 0xF), a < r8Value);
}

void CPU::cp_hl()
{
	// Update (HL)
	pushToQueue([&]()
				{ R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
			u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
			u8 a = ctx.regs().a;
			ctx.regs().setFlags((a - r8Value) == 0, 1, (a & 0xF) < (r8Value & 0xF), a < r8Value); });
}

void CPU::add_n()
{
	// Update A from imm8
	pushToQueue([&]()
				{		u8 previousAValue = ctx.regs().a;
        u8 r8Value = ctx.mem().readMem(ctx.regs().pc++);
        u16 newValue16 = previousAValue + r8Value;
        u8 newValue8 = (u8)newValue16;
        ctx.regs().a = newValue8;
        ctx.regs().setFlags(newValue8 == 0, 0, ((previousAValue & 0xF) + (r8Value & 0xF)) > 0xF, newValue16 > 0xFF); });
}

void CPU::adc_n()
{
	// Update A from imm8
	pushToQueue([&]()
				{ u8 previousAValue = ctx.regs().a;
        u8 r8Value = ctx.mem().readMem(ctx.regs().pc++);
        bool carry = ctx.regs().getCFlag();
        u16 newValue16 = previousAValue + r8Value + carry;
        u8 newValue8 = (u8)newValue16;
        ctx.regs().a = newValue8;
        ctx.regs().setFlags(newValue8 == 0, 0, ((previousAValue & 0xF) + (r8Value & 0xF) + carry) > 0xF, newValue16 > 0xFF); });
}

void CPU::sub_n()
{
	// Update A from imm8
	pushToQueue([&]()
				{   u8 previousAValue = ctx.regs().a;
        u8 r8Value = ctx.mem().readMem(ctx.regs().pc++);
        u8 newValue8 = previousAValue - r8Value;
        ctx.regs().a = newValue8;
        ctx.regs().setFlags(newValue8 == 0, 1, ((int)(previousAValue & 0xF) - (int)(r8Value & 0xF)) < 0, ((int)previousAValue - (int)r8Value) < 0); });
}

void CPU::sbc_n()
{
	// Update A from imm8
	pushToQueue([&]()
				{   u8 previousAValue = ctx.regs().a;
        u8 r8Value = ctx.mem().readMem(ctx.regs().pc++);
        bool carry = ctx.regs().getCFlag();
        u8 newValue8 = previousAValue - r8Value - carry;
        ctx.regs().a = newValue8;
        ctx.regs().setFlags(newValue8 == 0, 1, ((int)(previousAValue & 0xF) - (int)(r8Value & 0xF) - carry) < 0, ((int)previousAValue - (int)r8Value - carry) < 0); });
}

void CPU::and_n()
{
	// Update A from imm8
	pushToQueue([&]()
				{   u8 previousAValue = ctx.regs().a;
        u8 r8Value = ctx.mem().readMem(ctx.regs().pc++);
        u8 newValue = ctx.regs().a & r8Value;
        ctx.regs().a = newValue;
        ctx.regs().setFlags(newValue == 0, 0, 1, 0); });
}

void CPU::xor_n()
{
	// Update A from imm8
	pushToQueue([&]()
				{   u8 previousAValue = ctx.regs().a;
        u8 r8Value = ctx.mem().readMem(ctx.regs().pc++);
        u8 newValue = ctx.regs().a ^ r8Value;
        ctx.regs().a = newValue;
        ctx.regs().setFlags(newValue == 0, 0, 0, 0); });
}

void CPU::or_n()
{
	// Update A from imm8
	pushToQueue([&]()
				{   u8 previousAValue = ctx.regs().a;
        u8 r8Value = ctx.mem().readMem(ctx.regs().pc++);
        u8 newValue = ctx.regs().a | r8Value;
        ctx.regs().a = newValue;
        ctx.regs().setFlags(newValue == 0, 0, 0, 0); });
}

void CPU::cp_n()
{
	// Update A from imm8
	pushToQueue([&]()
				{   u8 previousAValue = ctx.regs().a;
        u8 r8Value = ctx.mem().readMem(ctx.regs().pc++);
        u8 a = ctx.regs().a;
        ctx.regs().setFlags((a - r8Value) == 0, 1, (a & 0xF) < (r8Value & 0xF), a < r8Value); });
}

void CPU::ret_cc()
{
	COND cond = Registers::getCONDFromCode((opCode() & 0b00011000) >> 3);
	auto low = std::make_shared<u8>();
	auto high = std::make_shared<u8>();
	if (ctx.regs().checkCOND(cond))
	{
		// Read SP low
		pushToQueue([&, low]()
					{ *low = ctx.mem().readMem(ctx.regs().sp++); });
		// Read SP high
		pushToQueue([&, high]()
					{ *high = ctx.mem().readMem(ctx.regs().sp++); });
		// Write SP to PC
		pushToQueue([&, low, high]()
					{ u16 addr = (*high << 8) | *low;
				ctx.regs().pc = addr; });
	}
	// Wait
	pushToQueue([]() { /*Internal*/ });
}

void CPU::ret()
{
	auto low = std::make_shared<u8>();
	auto high = std::make_shared<u8>();
	// Read SP low
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().sp++); });
	// Read SP high
	pushToQueue([&, high]()
				{ *high = ctx.mem().readMem(ctx.regs().sp++); });
	// Write SP to PC
	pushToQueue([&, low, high]()
				{ u16 addr = (*high << 8) | *low;
				ctx.regs().pc = addr; });
}

void CPU::reti()
{
	auto low = std::make_shared<u8>();
	auto high = std::make_shared<u8>();
	// Read SP low
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().sp++); });
	// Read SP high
	pushToQueue([&, high]()
				{ *high = ctx.mem().readMem(ctx.regs().sp++); });
	// Write SP to PC + Enable interrupts
	pushToQueue([&, low, high]()
				{ u16 addr = (*high << 8) | *low;
				ctx.regs().pc = addr;
				ctx.cpu().getInterrupts().setEnablingIME(true);
        		ctx.cpu().getInterrupts().setIMEDelay(1); });
}

void CPU::jp_cc_nn()
{
	COND cond = Registers::getCONDFromCode((opCode() & 0b00011000) >> 3);
	auto low = std::make_shared<u8>();
	auto high = std::make_shared<u8>();
	// Read low
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	// Read high
	pushToQueue([&, high]()
				{ *high = ctx.mem().readMem(ctx.regs().pc++); });
	if (ctx.regs().checkCOND(cond))
	{
		// If cond true, jump to absolute address
		pushToQueue([&, low, high]()
					{ ctx.regs().pc = (*high << 8) + *low; });
	}
}

void CPU::jp_nn()
{
	auto low = std::make_shared<u8>();
	auto high = std::make_shared<u8>();
	// Read low
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	// Read high
	pushToQueue([&, high]()
				{ *high = ctx.mem().readMem(ctx.regs().pc++); });
	// Jump to absolute address
	pushToQueue([&, low, high]()
				{ ctx.regs().pc = (*high << 8) + *low; });
}

void CPU::jp_hl()
{
	// Jump to address in (HL)
	ctx.regs().pc = ctx.regs().getFromR16(R16::HL);
}

void CPU::call_cc_nn()
{
	COND cond = Registers::getCONDFromCode((opCode() & 0b00011000) >> 3);
	auto low = std::make_shared<u8>();
	auto high = std::make_shared<u8>();
	// Read low
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	// Read high
	pushToQueue([&, high]()
				{ *high = ctx.mem().readMem(ctx.regs().pc++); });
	if (ctx.regs().checkCOND(cond))
	{
		// Write low PC to SP
		pushToQueue([&]()
					{ u16 pc = ctx.regs().pc;
        		ctx.regs().sp--;
        		ctx.mem().writeMem(ctx.regs().sp, pc >> 8); });
		// Write high PC to SP
		pushToQueue([&]()
					{ u16 pc = ctx.regs().pc;
        		ctx.regs().sp--;
        		ctx.mem().writeMem(ctx.regs().sp, pc & 0XFF); });
		// Jump to imm16
		pushToQueue([&, low, high]()
					{u16 newValue = (*high << 8) | *low;
        		ctx.regs().pc = newValue; });
	}
}

void CPU::call_nn()
{
	auto low = std::make_shared<u8>();
	auto high = std::make_shared<u8>();
	// Read low
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	// Read high
	pushToQueue([&, high]()
				{ *high = ctx.mem().readMem(ctx.regs().pc++); });
	// Write low PC to SP
	pushToQueue([&]()
				{ u16 pc = ctx.regs().pc;
        		ctx.regs().sp--;
        		ctx.mem().writeMem(ctx.regs().sp, pc >> 8); });
	// Write high PC to SP
	pushToQueue([&]()
				{ u16 pc = ctx.regs().pc;
        		ctx.regs().sp--;
        		ctx.mem().writeMem(ctx.regs().sp, pc & 0XFF); });
	// Jump to imm16
	pushToQueue([&, low, high]()
				{ u16 newValue = (*high << 8) | *low;
        		ctx.regs().pc = newValue; });
}

void CPU::rst_n()
{

	// Write low PC to SP
	pushToQueue([&]()
				{ u16 pc = ctx.regs().pc;
        		ctx.regs().sp--;
        		ctx.mem().writeMem(ctx.regs().sp, pc >> 8); });
	// Write high PC to SP
	pushToQueue([&]()
				{ u16 pc = ctx.regs().pc;
        		ctx.regs().sp--;
        		ctx.mem().writeMem(ctx.regs().sp, pc & 0XFF); });
	// Jump to imm16
	pushToQueue([&]()
				{ u8 tgt3 = Registers::getTGT3FromCode((opCode() & 0b00111000) >> 3);
				u8 high = tgt3 >> 8;
        		u8 low = tgt3 & 0xFF;
				u16 newValue = (high << 8) | low;
        		ctx.regs().pc = newValue; });
}

void CPU::pop_rr()
{
	auto low = std::make_shared<u8>();
	// Read SP low
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().sp++); });
	// Read SP high then write to R16_STK
	pushToQueue([&, low]()
				{ u8 high = ctx.mem().readMem(ctx.regs().sp++);
					R16_STK r16Stk = Registers::getR16StkFromCode((opCode() & 0b00110000) >> 4);
					u16 newValue = (high << 8) | *low;
        			ctx.regs().setRegFromR16Stk(r16Stk, newValue); });
}

void CPU::push_rr()
{
	R16_STK r16Stk = Registers::getR16StkFromCode((opCode() & 0b00110000) >> 4);
	pushToQueue([]() { /*Internal*/ });
	// Push low RR to SP
	pushToQueue([&, r16Stk]()
				{ u16 r16StkValue = ctx.regs().getFromR16Stk(r16Stk);
        	ctx.regs().sp--;
        	ctx.mem().writeMem(ctx.regs().sp, r16StkValue >> 8); });
	// Push high RR to SP
	pushToQueue([&, r16Stk]()
				{ u16 r16StkValue = ctx.regs().getFromR16Stk(r16Stk);
        	ctx.regs().sp--;
        	ctx.mem().writeMem(ctx.regs().sp, r16StkValue & 0xFF); });
}

void CPU::ldh_c_a()
{
	// Set address 0xFF(C) to A
	pushToQueue([&]()
				{ u8 low = ctx.regs().c;
        u16 address = 0xFF00 | low;
        ctx.mem().writeMem(address, ctx.regs().a); });
}

void CPU::ldh_n_a()
{
	auto low = std::make_shared<u8>();
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	// Update address from A
	pushToQueue([&, low]()
				{ u16 address = 0xFF00 | *low;
        ctx.mem().writeMem(address, ctx.regs().a); });
}

void CPU::ld_nn_a()
{
	auto low = std::make_shared<u8>();
	auto high = std::make_shared<u8>();
	// Read low
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	// Read high
	pushToQueue([&, high]()
				{ *high = ctx.mem().readMem(ctx.regs().pc++); });
	// Write A to address
	pushToQueue([&, low, high]()
				{ u16 address = (*high << 8) | *low;
        ctx.mem().writeMem(address, ctx.regs().a); });
}

void CPU::ldh_a_c()
{
	// Write value at address 0xFF(C) to C
	pushToQueue([&]()
				{ u8 low = ctx.regs().c;
        u16 address = 0xFF00 | low;
        ctx.regs().a = ctx.mem().readMem(address); });
}

void CPU::ldh_a_n()
{
	auto low = std::make_shared<u8>();
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	// Update A from address
	pushToQueue([&, low]()
				{ u16 address = 0xFF00 | *low;
        ctx.regs().a = ctx.mem().readMem(address); });
}

void CPU::ld_a_nn()
{
	auto low = std::make_shared<u8>();
	auto high = std::make_shared<u8>();
	// Read low
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	// Read high
	pushToQueue([&, high]()
				{ *high = ctx.mem().readMem(ctx.regs().pc++); });
	// Update A from address
	pushToQueue([&, low, high]()
				{ u16 address = (*high << 8) | *low;
        ctx.regs().a = ctx.mem().readMem(address); });
}

void CPU::add_sp_e()
{
	std::cout << "add_sp_e not implemented" << std::endl;
	ctx.setRunning(false);
}

void CPU::ld_hl_sp_e()
{
	auto low = std::make_shared<u8>();
	// Read value at address
	pushToQueue([&, low]()
				{ *low = ctx.mem().readMem(ctx.regs().pc++); });
	// Set (HL)
	pushToQueue([&, low]()
				{ u16 sp = ctx.regs().sp;
				i8 r8Value = (i8)*low;
				ctx.regs().setRegFromR16(R16::HL, sp +r8Value);
				ctx.regs().setFlags(0, 0, ((sp & 0xF) + (r8Value & 0xF)) > 0xF, ((sp & 0xFF) + r8Value) > 0xFF); });
}

void CPU::ld_sp_hl()
{
	// Set HL to SP
	pushToQueue([&]()
				{ ctx.regs().sp = (ctx.regs().h << 8) | ctx.regs().l; });
}

void CPU::di()
{
	// Cancel EI scheduling
	ctx.cpu().getInterrupts().setEnablingIME(false);
	ctx.cpu().getInterrupts().setIMEDelay(0);
	// Disable interrupts
	ctx.cpu().getInterrupts().setIME(false);
}

void CPU::ei()
{
	// Schedule enable interrupts
	ctx.cpu().getInterrupts().setEnablingIME(true);
	ctx.cpu().getInterrupts().setIMEDelay(1);
}

void CPU::rlc_r()
{
	// Update value directly
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	bool b7 = Common::getBit(r8Value, 7);
	u8 newValue = (r8Value << 1) | b7;
	ctx.regs().setRegFromR8(r8, newValue);
	ctx.regs().setFlags(newValue == 0, 0, 0, b7);
}

void CPU::rlc_hl()
{
	auto low = std::make_shared<u8>();
	// Update value at (HL)
	pushToQueue([&, low]()
				{ u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
				bool b7 = Common::getBit(r8Value, 7);
				u8 newValue = (r8Value << 1) | b7;
				*low = newValue;
				ctx.regs().setFlags(newValue == 0, 0, 0, b7); });
	// Write value to (HL)
	pushToQueue([&, low]()
				{ ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), *low); });
}

void CPU::rrc_r()
{
	// Update value directly
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	bool b0 = Common::getBit(r8Value, 0);
	u8 newValue = (r8Value >> 1) | (b0 << 7);
	ctx.regs().setRegFromR8(r8, newValue);
	ctx.regs().setFlags(newValue == 0, 0, 0, b0);
}

void CPU::rrc_hl()
{
	auto low = std::make_shared<u8>();
	// Update value at (HL)
	pushToQueue([&, low]()
				{ u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
				bool b0 = Common::getBit(r8Value, 0);
				u8 newValue = (r8Value >> 1) | (b0 << 7);
				*low = newValue;
				ctx.regs().setFlags(newValue == 0, 0, 0, b0); });
	// Write value to (HL)
	pushToQueue([&, low]()
				{ ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), *low); });
}

void CPU::rl_r()
{
	// Update value directly
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	bool b7 = Common::getBit(r8Value, 7);
	bool carry = ctx.regs().getCFlag();
	u8 newValue = (r8Value << 1) | carry;
	ctx.regs().setRegFromR8(r8, newValue);
	ctx.regs().setFlags(newValue == 0, 0, 0, b7);
}

void CPU::rl_hl()
{
	auto low = std::make_shared<u8>();
	// Update value at (HL)
	pushToQueue([&, low]()
				{ u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
				bool b7 = Common::getBit(r8Value, 7);
				bool carry = ctx.regs().getCFlag();
				u8 newValue = (r8Value << 1) | carry;
				*low = newValue;
				ctx.regs().setFlags(newValue == 0, 0, 0, b7); });
	// Write value to (HL)
	pushToQueue([&, low]()
				{ ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), *low); });
}

void CPU::rr_r()
{
	// Update value directly
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	bool b0 = Common::getBit(r8Value, 0);
	bool carry = ctx.regs().getCFlag();
	u8 newValue = (r8Value >> 1) | (carry << 7);
	ctx.regs().setRegFromR8(r8, newValue);
	ctx.regs().setFlags(newValue == 0, 0, 0, b0);
}

void CPU::rr_hl()
{
	auto low = std::make_shared<u8>();
	// Update value at (HL)
	pushToQueue([&, low]()
				{ u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
				bool b0 = Common::getBit(r8Value, 0);
				bool carry = ctx.regs().getCFlag();
				u8 newValue = (r8Value >> 1) | (carry << 7);
				*low = newValue;
				ctx.regs().setFlags(newValue == 0, 0, 0, b0); });
	// Write value to (HL)
	pushToQueue([&, low]()
				{ ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), *low); });
}

void CPU::sla_r()
{
	// Update value directly
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	bool carry = Common::getBit(r8Value, 7);
	u8 newValue = (r8Value << 1);
	ctx.regs().setRegFromR8(r8, newValue);
	ctx.regs().setFlags(newValue == 0, 0, 0, carry);
}

void CPU::sla_hl()
{
	auto low = std::make_shared<u8>();
	// Update value at (HL)
	pushToQueue([&, low]()
				{ u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
				bool carry = Common::getBit(r8Value, 7);
				u8 newValue = (r8Value << 1);
				*low = newValue;
				ctx.regs().setFlags(newValue == 0, 0, 0, carry); });
	// Write value to (HL)
	pushToQueue([&, low]()
				{ ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), *low); });
}

void CPU::sra_r()
{
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	bool b0 = Common::getBit(r8Value, 0);
	bool b7 = Common::getBit(r8Value, 7);
	u8 newValue = (r8Value >> 1) | (b7 << 7);
	ctx.regs().setRegFromR8(r8, newValue);
	ctx.regs().setFlags(newValue == 0, 0, 0, b0);
}

void CPU::sra_hl()
{
	auto low = std::make_shared<u8>();
	// Update value at (HL)
	pushToQueue([&, low]()
				{ u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
				bool b0 = Common::getBit(r8Value, 0);
				bool b7 = Common::getBit(r8Value, 7);
				u8 newValue = (r8Value >> 1) | (b7 << 7);
				*low = newValue;
				ctx.regs().setFlags(newValue == 0, 0, 0, b0); });
	// Write value to (HL)
	pushToQueue([&, low]()
				{ ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), *low); });
}

void CPU::swap_r()
{
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	u8 newValue = ((r8Value & 0xF) << 4) + ((r8Value & 0xF0) >> 4);
	ctx.regs().setRegFromR8(r8, newValue);
	ctx.regs().setFlags(newValue == 0, 0, 0, 0);
}

void CPU::swap_hl()
{
	auto low = std::make_shared<u8>();
	// Update value at (HL)
	pushToQueue([&, low]()
				{ u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
				bool carry = Common::getBit(r8Value, 7);
				u8 newValue = ((r8Value & 0xF) << 4) + ((r8Value & 0xF0) >> 4);
				*low = newValue;
				ctx.regs().setFlags(newValue == 0, 0, 0, 0); });
	// Write value to (HL)
	pushToQueue([&, low]()
				{ ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), *low); });
}

void CPU::srl_r()
{
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	bool carry = Common::getBit(r8Value, 0);
	u8 newValue = (r8Value >> 1);
	ctx.regs().setRegFromR8(r8, newValue);
	ctx.regs().setFlags(newValue == 0, 0, 0, carry);
}

void CPU::srl_hl()
{
	auto low = std::make_shared<u8>();
	// Update value at (HL)
	pushToQueue([&, low]()
				{ u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
				bool carry = Common::getBit(r8Value, 0);
				u8 newValue = (r8Value >> 1);
				*low = newValue;
				ctx.regs().setFlags(newValue == 0, 0, 0, carry); });
	// Write value to (HL)
	pushToQueue([&, low]()
				{ ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), *low); });
}

void CPU::bit_b_r()
{
	u8 b = (cbPrefixOpCode() & 0b00111000) >> 3;
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	bool isBitSet = Common::getBit(r8Value, b);
	ctx.regs().setFlags(!isBitSet, 0, 1, -1);
}

void CPU::bit_b_hl()
{
	// Update flags from (HL)
	pushToQueue([&]()
				{ 	u8 b = (cbPrefixOpCode() & 0b00111000) >> 3;
				u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
				u8 newValue = (r8Value >> 1);
				bool isBitSet = Common::getBit(r8Value, b);
				ctx.regs().setFlags(!isBitSet, 0, 1, -1); });
}

void CPU::res_b_r()
{
	u8 b = (cbPrefixOpCode() & 0b00111000) >> 3;
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	u8 newValue = Common::resetBit(r8Value, b);
	ctx.regs().setRegFromR8(r8, newValue);
}

void CPU::res_b_hl()
{
	auto low = std::make_shared<u8>();
	// Update flags from (HL)
	pushToQueue([&, low]()
				{ u8 b = (cbPrefixOpCode() & 0b00111000) >> 3;
		u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
		*low = Common::resetBit(r8Value, b); });
	// Write value to (HL)
	pushToQueue([&, low]()
				{ ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), *low); });
}

void CPU::set_b_r()
{
	u8 b = (cbPrefixOpCode() & 0b00111000) >> 3;
	R8 r8 = Registers::getR8FromCode(cbPrefixOpCode() & 0b111);
	u8 r8Value = ctx.regs().getFromR8(r8);
	u8 newValue = Common::setBit(r8Value, b);
	ctx.regs().setRegFromR8(r8, newValue);
}

void CPU::set_b_hl()
{
	auto low = std::make_shared<u8>();
	// Update flags from (HL)
	pushToQueue([&, low]()
				{ u8 b = (cbPrefixOpCode() & 0b00111000) >> 3;
		u8 r8Value = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
		*low = Common::setBit(r8Value, b); });
	// Write value to (HL)
	pushToQueue([&, low]()
				{ ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), *low); });
}