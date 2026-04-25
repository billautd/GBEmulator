#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "Test LD BC,d16 operation for code 0x01", "[lb_bc_imm16_0x01]")
{
	ctx->mem().at(0x01) = 0xAB;
	ctx->mem().at(0x02) = 0xCD;
	ctx->cpu().runOp(0x01);

	// Check registers and PC
	ASSERT_REGISTERS(0, 0xCD, 0xAB, 0, 0, 0, 0, 0, 0, 0, 3);
}
