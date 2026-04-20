#include "../include/Operations.h"
#include "../include/Context.h"

Context* ctx() { return Context::get(); }
Registers& regs() { return ctx()->getRegisters(); }
u8 opCode() { return ctx()->getCurrentOpCode(); }
std::vector<u8>& memory() { return ctx()->getMemory(); };

void Operations::runOp() {
	u8 code = memory().at(regs().pc);
	ctx()->setCurrentOpCode(code);

	regs().log();
	std::cout << "Current op code : " << Common::toHexStr(code) << std::endl;

	//Block 0
	//0x00
	if (code == 0) {
		std::cout << "nop" << std::endl;
		nop();
	}
	//0x01 (BC), 0x11 (DE), 0x21 (HL), 0x31 (SP)
	else if ((code & 0b11000000) == 0 && (code & 0b1111) == 1) {
		std::cout << "ld_r16_imm16" << std::endl;
		ld_r16_imm16();
	}
	//0x02 (BC), 0x12 (DE), 0x22 (HL+), 0x32 (HL-)
	else if ((code & 0b11000000) == 0 && (code & 0b1111) == 2) {
		std::cout << "ld_r16mem_a" << std::endl;
		ld_r16mem_a();
	}
	//0x05 (B), 0x0D (C), 0x15 (D), 0x1D (E), 0x25 (H), 0x2D (L), 0x35 (HL), 0x3D (A)
	else if ((code & 0b11000000) == 0 && (code & 0b111) == 5) {
		std::cout << "dec r8" << std::endl;
		dec_r8();
	}
	//0x06 (B), 0x0E (C), 0x16 (D), 0x1E (E), 0x26 (H), 0x2E (L), 0x36 (HL), 0x3E (A)
	else if ((code & 0b11000000) == 0 && (code & 0b111) == 0b110){
		std::cout << "ld_r8_imm8" << std::endl;
		ld_r8_imm8();
	}
	//0x20 (NZ), 0x28 (Z), 0x30 (NC), 0x38 (C)
	//else if((code & 0b11100000) == 0b100000 && (code & 0b111) == 0) {
	//	std::cout << "jr cond_imm8" << std::endl;
	//	jr_cond_imm8();
	//}
	//Block 1 : 8-bit reg to reg loads
	//Block 2 : 8-bit arithmetic
	//0xA8 (B), 0xA9 (C), 0xAA (D), 0xAB (E), 0xAC (H), OxAD (L), OxAE (HL), 0xAF (A)
	else if ((code & 0b11111000) == 0b10101000) {
		std::cout << "xor_a_r8" << std::endl;
		xor_a_r8();
	}
	//Block 3
	//0xC3
	else if (code == 0b11000011) {
		std::cout << "jp_imm16" << std::endl;
		jp_imm16();
	}
	//$CB prefix
	else {
		std::cerr << "Op code " << Common::toHexStr(code) << " not managed" << std::endl;
		ctx()->setRunning(false);
	}
}

/**************************************/
/**              Block 0             **/
/**************************************/
void Operations::nop() {
	regs().pc++;
}

void Operations::ld_r16_imm16() {
	u16 imm16 = regs().imm16();

	R16 r16 = Registers::getR16FromCode((opCode() & 0b110000) >> 4);
	regs().setRegFromR16(r16, imm16);

	std::cout << "ld_r16_imm16 : " << Common::toHexStr(imm16) << " set to " << R16_STR[(int)r16] << std::endl;

	regs().pc+=3;
}

void Operations::ld_r16mem_a() {
	R16_MEM r16Mem = Registers::getR16MemFromCode((opCode() & 0b110000) >> 4);
	u16 address = regs().getPointerFromR16Mem(r16Mem);
	memory().at(address) = regs().a;

	//HLI or HLD -> update HL after writing
	regs().updateHLMem(r16Mem);

	std::cout << "ld_r16mem_a : " << Common::toHexStr(regs().a) << " set to address " << Common::toHexStr(address) <<
		"from register" << R16_STR[(int)r16Mem] << std::endl;

	regs().pc++;
}

void Operations::dec_r8() {
	R8 r8 = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
	regs().setRegFromR8(r8, regs().getFromR8(r8) - 1);

	regs().setFlags(regs().getFromR8(r8) == 0, 1, (regs().getFromR8(r8) & 0xF) == 0xF, -1);

	std::cout << "dec_r8 : " << R8_STR[(int)r8] << " decremented" << std::endl;
	regs().pc++;
}

void Operations::ld_r8_imm8() {
	u8 imm8 = regs().imm8();

	R8 r8 = Registers::getR8FromCode((opCode() & 0b111000) >> 3);
	regs().setRegFromR8(r8, imm8);

	std::cout << "ld_r8_imm8 : " << Common::toHexStr(imm8) << " set to " << R8_STR[(int)r8] << std::endl;

	regs().pc += 2;
}

void Operations::jr_cond_imm8() {
	u8 imm8 = regs().imm8();
	//Get condition and jump relative to current PC
	regs().pc += 2;
}

/**************************************/
/** Block 1 : 8-bit reg to reg loads **/
/**************************************/
 
/**************************************/
/**     Block 2 : 8-bit arithmetic   **/
/**************************************/
void Operations::xor_a_r8() {
	R8 r8 = Registers::getR8FromCode(opCode() & 0b111);
	u8 r8Value = regs().getFromR8(r8);
	regs().a ^= r8Value;

	regs().setFlags(regs().a == 0, 0, 0, 0);

	std::cout << "xor_a_r8 with " << R8_STR[(int)r8] << std::endl;
	regs().pc++;
}
/**************************************/
/**              Block 3             **/
/**************************************/
void Operations::jp_imm16() {
	u16 imm16 = regs().imm16();
	//JP to address given
	regs().pc = imm16;
	std::cout << "jp_imm16 : " << Common::toHexStr(imm16) << std::endl;
}

/**************************************/
/**           $CB prefix             **/
/**************************************/