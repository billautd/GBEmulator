#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x27", "[cpu_ops_daa]")
{
    regs().a = 0xAB;
    regs().f = 0b11110000;
    runOp(0x27);
    ASSERT_REGISTERS(0x45, 0, 0, 0, 0, 0b01010000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    runOp(0x27);
    ASSERT_REGISTERS(0x11, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x09;
    regs().f = 0b00100000;
    runOp(0x27);
    ASSERT_REGISTERS(0x0F, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xFF;
    regs().f = 0b01000000;
    runOp(0x27);
    ASSERT_REGISTERS(0xFF, 0, 0, 0, 0, 0b01000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}