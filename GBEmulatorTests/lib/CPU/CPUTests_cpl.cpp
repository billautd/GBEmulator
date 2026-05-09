#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x2F", "[cpu_ops_cpl]")
{
    regs().a = 0b10110010;

    runOp(0x2F);

    ASSERT_REGISTERS(0b01001101, 0, 0, 0, 0, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);
}