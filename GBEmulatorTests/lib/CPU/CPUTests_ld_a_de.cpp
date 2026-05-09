#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x1A", "[cpu_ops_ld_a_de]")
{
    // Value to copy
    mem(0xABCD) = 0xEF;
    // Byte pointed to
    regs().d = 0xAB;
    regs().e = 0xCD;

    runOp(0x1A);

    ASSERT_REGISTERS(0xEF, 0, 0, 0xAB, 0xCD, 0, 0, 0, 0, 1);
    REQUIRE(mem(0xABCD) == 0xEF);
    REQUIRE(ticks() == 8);
}