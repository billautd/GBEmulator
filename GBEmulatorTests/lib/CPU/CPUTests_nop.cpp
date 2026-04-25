#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "Test nop operation for code 0x00", "[nop_0x00]")
{
	ctx->cpu().runOp(0x00);

	// Check registers and PC
	ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
}