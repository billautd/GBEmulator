#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x36", "[cpu_ops_ld_hl_n]")
{
    // Byte pointed to
    regs().h = 0x12;
    regs().l = 0x34;

    mem(0x01) = 0xAB;
    runOp(0x36);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0x12, 0x34, 0, 2);
    REQUIRE(mem(0x1234) == 0xAB);
    REQUIRE(ticks() == 12);
}