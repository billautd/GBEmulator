#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x00", "[cpu_ops_nop]")
{
	runOp(0x00);

	// Check registers and PC
	ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
	REQUIRE(ticks() == 4);

	runOp(0x00);

	// Check registers and PC
	ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 2);
	REQUIRE(ticks() == 8);
}