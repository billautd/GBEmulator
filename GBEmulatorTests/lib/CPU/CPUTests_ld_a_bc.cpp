#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x0A", "[cpu_ops_ld_a_bc]")
{
    // Value to copy
    mem(0xABCD) = 0xEF;
    // Byte pointed to
    regs().b = 0xAB;
    regs().c = 0xCD;

    runOp(0x0A);

    ASSERT_REGISTERS(0xEF, 0xAB, 0xCD, 0, 0, 0, 0, 0, 0, 1);
    REQUIRE(mem(0xABCD) == 0xEF);
    REQUIRE(ticks() == 8);
}