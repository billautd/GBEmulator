#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x37", "[cpu_ops_scf]")
{
    regs().f = 0b11110000;
    runOp(0x37);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10010000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().f = 0b00010000;

    runOp(0x37);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}