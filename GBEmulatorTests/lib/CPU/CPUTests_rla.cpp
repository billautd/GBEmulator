#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x17", "[cpu_ops_rla]")
{
    regs().a = 0b11000011;
    regs().f = 0b00010000;

    runOp(0x17);

    ASSERT_REGISTERS(0b10000111, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0b01000011;
    regs().f = 0b00010000;

    runOp(0x17);

    ASSERT_REGISTERS(0b10000111, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01100010;
    regs().f = 0b00000000;

    runOp(0x17);

    ASSERT_REGISTERS(0b11000100, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0b11100010;
    regs().f = 0b00000000;

    runOp(0x17);

    ASSERT_REGISTERS(0b11000100, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}