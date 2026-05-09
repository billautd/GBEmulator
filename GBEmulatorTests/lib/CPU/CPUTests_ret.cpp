#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xC9", "[cpu_ops_ret]")
{
    regs().sp = 0xCFFD;
    mem(0xCFFD) = 0x12;
    mem(0xCFFE) = 0x34;

    runOp(0xC9);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0xCFFF, 0x3412);
    REQUIRE(ticks() == 16);
}