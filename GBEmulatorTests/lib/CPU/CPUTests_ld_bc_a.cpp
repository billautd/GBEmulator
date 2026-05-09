#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x02", "[cpu_ops_ld_bc_a]")
{
	// Value to copy
	regs().a = 0xEF;
	// Byte pointed to
	regs().b = 0xAB;
	regs().c = 0xCD;

	runOp(0x02);

	ASSERT_REGISTERS(0xEF, 0xAB, 0xCD, 0, 0, 0, 0, 0, 0, 1);
	REQUIRE(mem(0xABCD) == 0xEF);
	REQUIRE(ticks() == 8);
}