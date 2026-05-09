#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xE9", "[cpu_ops_jp_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    runOp(0xE9);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 0xABCD);
    REQUIRE(ticks() == 4);
}