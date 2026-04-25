#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "Test LD [BC],A operation for code 0x01", "[lb_bc_a_0x02]")
{
	// Value to copy
	ctx->regs().a = 0xEF;
	// Byte pointed to
	ctx->regs().b = 0xAB;
	ctx->regs().c = 0xCD;

	ctx->cpu().runOp(0x02);

	// Check registers and PC
	ASSERT_REGISTERS(0xEF, 0xAB, 0xCD, 0, 0, 0, 0, 0, 0, 0, 1);
	// Check memory
	REQUIRE(ctx->mem().at(0xABCD) == 0xEF);
}
