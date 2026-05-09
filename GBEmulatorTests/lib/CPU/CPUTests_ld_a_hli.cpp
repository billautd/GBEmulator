#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x2A", "[cpu_ops_ld_a_hli]")
{
    // Value to copy
    mem(0xABCD) = 0xEF;
    // Byte pointed to
    regs().h = 0xAB;
    regs().l = 0xCD;

    runOp(0x2A);

    ASSERT_REGISTERS(0xEF, 0, 0, 0, 0, 0, 0xAB, 0xCE, 0, 1);
    REQUIRE(mem(0xABCD) == 0xEF);
    REQUIRE(ticks() == 8);
}