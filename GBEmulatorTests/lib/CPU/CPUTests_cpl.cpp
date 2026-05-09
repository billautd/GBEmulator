#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x2F", "[cpu_ops_cpl]")
{
    regs().a = 0b10110010;
    regs().f = 0b10010000;

    runOp(0x2F);

    ASSERT_REGISTERS(0b01001101, 0, 0, 0, 0, 0b11110000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0b11110011;
    regs().f = 0b00000000;

    runOp(0x2F);

    ASSERT_REGISTERS(0b00001100, 0, 0, 0, 0, 0b01100000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}