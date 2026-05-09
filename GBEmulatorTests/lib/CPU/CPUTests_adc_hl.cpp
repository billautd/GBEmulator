#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x8E", "[cpu_ops_adc_hl]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0x10;
    runOp(0x8E);
    ASSERT_REGISTERS(0xBC, 0, 0, 0, 0, 0b00000000, 0x12, 0x34, 0, 1);
    REQUIRE(mem(0x1234) == 0x10);
    REQUIRE(ticks() == 8);

    regs().a = 0xFE;
    regs().f = 0b00010000;
    mem(0x1234) = 0x01;
    runOp(0x8E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10110000, 0x12, 0x34, 0, 2);
    REQUIRE(mem(0x1234) == 0x01);
    REQUIRE(ticks() == 16);

    regs().a = 0x0E;
    regs().f = 0b00010000;
    mem(0x1234) = 0x01;
    runOp(0x8E);
    ASSERT_REGISTERS(0x10, 0, 0, 0, 0, 0b00100000, 0x12, 0x34, 0, 3);
    REQUIRE(mem(0x1234) == 0x01);
    REQUIRE(ticks() == 24);

    regs().a = 0x0E;
    regs().f = 0b00000000;
    mem(0x1234) = 0x01;
    runOp(0x8E);
    ASSERT_REGISTERS(0x0F, 0, 0, 0, 0, 0b00000000, 0x12, 0x34, 0, 4);
    REQUIRE(mem(0x1234) == 0x01);
    REQUIRE(ticks() == 32);
}