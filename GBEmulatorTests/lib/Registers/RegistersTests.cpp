#include <Registers.h>
#include <Context.h>
#include <catch2/catch_test_macros.hpp>

class RegisterTestsFixture
{
private:
	static int id;

protected:
	Context *ctx;
	Registers *regs;
	int getID()
	{
		return ++id;
	}

public:
	RegisterTestsFixture() : ctx(new Context()), regs(new Registers(*ctx))
	{
	}
};
int RegisterTestsFixture::id = 0;

TEST_CASE_METHOD(RegisterTestsFixture, "regs_getR8FromCoode", "[regs]")
{
	// Check correct R8 is returned
	REQUIRE(Registers::getR8FromCode(0) == R8::B);
	REQUIRE(Registers::getR8FromCode(1) == R8::C);
	REQUIRE(Registers::getR8FromCode(2) == R8::D);
	REQUIRE(Registers::getR8FromCode(3) == R8::E);
	REQUIRE(Registers::getR8FromCode(4) == R8::H);
	REQUIRE(Registers::getR8FromCode(5) == R8::L);
	REQUIRE(Registers::getR8FromCode(6) == R8::HL);
	REQUIRE(Registers::getR8FromCode(7) == R8::A);
	// Check assertion raised if wrong value
	REQUIRE_THROWS_AS(Registers::getR8FromCode(8), std::invalid_argument);
	REQUIRE_THROWS_AS(Registers::getR8FromCode(-1), std::invalid_argument);
}

TEST_CASE_METHOD(RegisterTestsFixture, "regs_setRegFromR8", "[regs]")
{
	// Set all registers through method
	regs->setRegFromR8(R8::B, 0x01);
	regs->setRegFromR8(R8::C, 0x02);
	regs->setRegFromR8(R8::D, 0x03);
	regs->setRegFromR8(R8::E, 0x04);
	regs->setRegFromR8(R8::H, 0x05);
	regs->setRegFromR8(R8::L, 0x06);
	regs->setRegFromR8(R8::HL, 0x07);
	regs->setRegFromR8(R8::A, 0x08);

	// Asserts updated registers
	REQUIRE(regs->b == 0x01);
	REQUIRE(regs->c == 0x02);
	REQUIRE(regs->d == 0x03);
	REQUIRE(regs->e == 0x04);
	REQUIRE(regs->h == 0x05);
	REQUIRE(regs->l == 0x06);
	REQUIRE(ctx->mem().at(0x0506) == 0X07);
	REQUIRE(regs->a == 0x08);
}

TEST_CASE_METHOD(RegisterTestsFixture, "regs_getFromR8", "[regs]")
{
	// Sets registers directly
	regs->b = 0x01;
	regs->c = 0x02;
	regs->d = 0x03;
	regs->e = 0x04;
	regs->h = 0x05;
	regs->l = 0x06;
	regs->a = 0x08;

	// Asserts correct values returned
	REQUIRE(regs->getFromR8(R8::B) == 0x01);
	REQUIRE(regs->getFromR8(R8::C) == 0x02);
	REQUIRE(regs->getFromR8(R8::D) == 0x03);
	REQUIRE(regs->getFromR8(R8::E) == 0x04);
	REQUIRE(regs->getFromR8(R8::H) == 0x05);
	REQUIRE(regs->getFromR8(R8::L) == 0x06);
	// REQUIRE(regs->getFromR8(R8::HL) == 0x07);
	REQUIRE(regs->getFromR8(R8::A) == 0x08);
}

TEST_CASE_METHOD(RegisterTestsFixture, "regs_getR16FromCode", "[regs]")
{
	REQUIRE(Registers::getR16FromCode(0) == R16::BC);
	REQUIRE(Registers::getR16FromCode(1) == R16::DE);
	REQUIRE(Registers::getR16FromCode(2) == R16::HL);
	REQUIRE(Registers::getR16FromCode(3) == R16::SP);
	REQUIRE_THROWS_AS(Registers::getR16FromCode(4), std::invalid_argument);
	REQUIRE_THROWS_AS(Registers::getR16FromCode(8), std::invalid_argument);
	REQUIRE_THROWS_AS(Registers::getR16FromCode(-1), std::invalid_argument);
}

TEST_CASE_METHOD(RegisterTestsFixture, "regs_setRegFromR16", "[regs]")
{
	// Set all registers through method
	regs->setRegFromR16(R16::BC, 0x0102);
	regs->setRegFromR16(R16::DE, 0x0304);
	regs->setRegFromR16(R16::HL, 0x0506);
	regs->setRegFromR16(R16::SP, 0x0708);

	// Asserts updated registers
	REQUIRE(regs->b == 0x01);
	REQUIRE(regs->c == 0x02);
	REQUIRE(regs->d == 0x03);
	REQUIRE(regs->e == 0x04);
	REQUIRE(regs->h == 0x05);
	REQUIRE(regs->l == 0x06);
	REQUIRE(regs->sp == 0x0708);
}

TEST_CASE_METHOD(RegisterTestsFixture, "regs_getFromR16", "[regs]")
{
	// Sets registers directly
	regs->b = 0x01;
	regs->c = 0x02;
	regs->d = 0x03;
	regs->e = 0x04;
	regs->h = 0x05;
	regs->l = 0x06;
	regs->a = 0x08;
	regs->sp = 0x1234;

	REQUIRE(regs->getFromR16(R16::BC) == 0x0102);
	REQUIRE(regs->getFromR16(R16::DE) == 0x0304);
	REQUIRE(regs->getFromR16(R16::HL) == 0x0506);
	REQUIRE(regs->getFromR16(R16::SP) == 0x1234);
}

TEST_CASE_METHOD(RegisterTestsFixture, "regs_getR16MemFromCode", "[regs]")
{
	REQUIRE(Registers::getR16MemFromCode(0) == R16_MEM::BC);
	REQUIRE(Registers::getR16MemFromCode(1) == R16_MEM::DE);
	REQUIRE(Registers::getR16MemFromCode(2) == R16_MEM::HLI);
	REQUIRE(Registers::getR16MemFromCode(3) == R16_MEM::HLD);
	REQUIRE_THROWS_AS(Registers::getR16MemFromCode(4), std::invalid_argument);
	REQUIRE_THROWS_AS(Registers::getR16MemFromCode(8), std::invalid_argument);
	REQUIRE_THROWS_AS(Registers::getR16MemFromCode(-1), std::invalid_argument);
}

TEST_CASE_METHOD(RegisterTestsFixture, "regs_getPointerFromR16Mem", "[regs]")
{
	// Sets registers directly
	regs->b = 0x01;
	regs->c = 0x02;
	regs->d = 0x03;
	regs->e = 0x04;
	regs->h = 0x05;
	regs->l = 0x06;
	// regs->hl = 0x07;
	regs->a = 0x08;

	// Asserts correct values returned
	REQUIRE(regs->getPointerFromR16Mem(R16_MEM::BC) == 0x0102);
	REQUIRE(regs->getPointerFromR16Mem(R16_MEM::DE) == 0x0304);
	REQUIRE(regs->getPointerFromR16Mem(R16_MEM::HLI) == 0x0506);
	REQUIRE(regs->getPointerFromR16Mem(R16_MEM::HLD) == 0x0506);
}

TEST_CASE_METHOD(RegisterTestsFixture, "regs_getCONDFromCode", "[regs]")
{
	REQUIRE(Registers::getCONDFromCode(0) == COND::NZ);
	REQUIRE(Registers::getCONDFromCode(1) == COND::Z);
	REQUIRE(Registers::getCONDFromCode(2) == COND::NC);
	REQUIRE(Registers::getCONDFromCode(3) == COND::C);
	REQUIRE_THROWS_AS(Registers::getCONDFromCode(4), std::invalid_argument);
	REQUIRE_THROWS_AS(Registers::getCONDFromCode(8), std::invalid_argument);
	REQUIRE_THROWS_AS(Registers::getCONDFromCode(-1), std::invalid_argument);
}

TEST_CASE_METHOD(RegisterTestsFixture, "regs_checkCOND", "[regs]")
{
	regs->f = 0b00000000;
	REQUIRE(regs->checkCOND(COND::NZ));
	REQUIRE_FALSE(regs->checkCOND(COND::Z));
	REQUIRE(regs->checkCOND(COND::NC));
	REQUIRE_FALSE(regs->checkCOND(COND::C));

	regs->f = 0b10000000;
	REQUIRE_FALSE(regs->checkCOND(COND::NZ));
	REQUIRE(regs->checkCOND(COND::Z));
	REQUIRE(regs->checkCOND(COND::NC));
	REQUIRE_FALSE(regs->checkCOND(COND::C));

	regs->f = 0b01000000;
	REQUIRE(regs->checkCOND(COND::NZ));
	REQUIRE_FALSE(regs->checkCOND(COND::Z));
	REQUIRE(regs->checkCOND(COND::NC));
	REQUIRE_FALSE(regs->checkCOND(COND::C));

	regs->f = 0b00100000;
	REQUIRE(regs->checkCOND(COND::NZ));
	REQUIRE_FALSE(regs->checkCOND(COND::Z));
	REQUIRE(regs->checkCOND(COND::NC));
	REQUIRE_FALSE(regs->checkCOND(COND::C));

	regs->f = 0b00010000;
	REQUIRE(regs->checkCOND(COND::NZ));
	REQUIRE_FALSE(regs->checkCOND(COND::Z));
	REQUIRE_FALSE(regs->checkCOND(COND::NC));
	REQUIRE(regs->checkCOND(COND::C));
}

TEST_CASE_METHOD(RegisterTestsFixture, "regs_imm8", "[regs]")
{
	regs->pc = 0x1020;

	ctx->mem().at(0x1020) = 0x01;
	ctx->mem().at(0x1021) = 0x02;
	ctx->mem().at(0x1022) = 0x03;

	REQUIRE(regs->imm8() == 0x01);
	REQUIRE(regs->imm8() == 0x02);
	REQUIRE(regs->imm8() == 0x03);
}

TEST_CASE_METHOD(RegisterTestsFixture, "regs_imm16", "[regs]")
{
	regs->pc = 0x1020;

	ctx->mem().at(0x1020) = 0x01;
	ctx->mem().at(0x1021) = 0x02;
	ctx->mem().at(0x1022) = 0x03;
	ctx->mem().at(0x1023) = 0x04;

	REQUIRE(regs->imm16() == 0x0201);
	REQUIRE(regs->imm16() == 0x0403);
}

TEST_CASE_METHOD(RegisterTestsFixture, "regs_updateHLMem", "[regs]")
{
	regs->h = 0x01;
	regs->l = 0x02;

	// Checks increment
	regs->updateHLMem(R16_MEM::HLI);
	REQUIRE(regs->h == 0x01);
	REQUIRE(regs->l == 0x03);

	// Checks decrement
	regs->updateHLMem(R16_MEM::HLD);
	REQUIRE(regs->h == 0x01);
	REQUIRE(regs->l == 0x02);

	// Checks unchanged
	regs->updateHLMem(R16_MEM::BC);
	REQUIRE(regs->h == 0x01);
	REQUIRE(regs->l == 0x02);

	regs->updateHLMem(R16_MEM::DE);
	REQUIRE(regs->h == 0x01);
	REQUIRE(regs->l == 0x02);
}

TEST_CASE_METHOD(RegisterTestsFixture, "Tests method setFlags", "[setFlags]")
{
	regs->f = 0x0000;
	regs->setFlags(1, 1, 1, 1);
	REQUIRE(regs->f == 0b11110000);

	regs->setFlags(1, 0, 1, 0);
	REQUIRE(regs->f == 0b10100000);

	regs->setFlags(-1, -1, -1, -1);
	REQUIRE(regs->f == 0b10100000);

	regs->setFlags(0, 0, 0, 0);
	REQUIRE(regs->f == 0b00000000);
}