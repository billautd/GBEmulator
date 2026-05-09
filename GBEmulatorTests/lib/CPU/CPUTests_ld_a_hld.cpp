#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x3A", "[cpu_ops_ld_a_hld]")
{
    // Value to copy
    mem(0xABCD) = 0xEF;
    // Byte pointed to
    regs().h = 0xAB;
    regs().l = 0xCD;

    runOp(0x3A);

    ASSERT_REGISTERS(0xEF, 0, 0, 0, 0, 0, 0xAB, 0xCC, 0, 1);
    REQUIRE(mem(0xABCD) == 0xEF);
    REQUIRE(ticks() == 8);
}