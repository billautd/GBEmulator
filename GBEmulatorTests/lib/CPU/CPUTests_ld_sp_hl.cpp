#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xF9", "[cpu_ops_ld_sp_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    runOp(0xF9);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0xABCD, 1);
    REQUIRE(ticks() == 8);

    regs().h = 0x02;
    regs().l = 0x01;
    runOp(0xF9);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0x02, 0x01, 0x0201, 2);
    REQUIRE(ticks() == 16);
}