#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x22", "[cpu_ops_ld_hli_a]")
{
	// Value to copy
	regs().a = 0xEF;
	// Byte pointed to
	regs().h = 0xAB;
	regs().l = 0xCD;

	runOp(0x22);

	ASSERT_REGISTERS(0xEF, 0, 0, 0, 0, 0, 0xAB, 0xCE, 0, 1);
	REQUIRE(mem(0xABCD) == 0xEF);
	REQUIRE(ticks() == 8);
}