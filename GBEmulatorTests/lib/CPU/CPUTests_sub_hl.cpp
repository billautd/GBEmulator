#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x96", "[cpu_ops_sub_hl]")
{
    regs().a = 0xAB;
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0x01;
    runOp(0x96);
    ASSERT_REGISTERS(0xAA, 0, 0, 0, 0, 0b01000000, 0x12, 0x34, 0, 1);
    REQUIRE(ticks() == 8);
    REQUIRE(mem(0x1234) == 0x01);

    regs().a = 0xAB;
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0x0F;
    runOp(0x96);
    ASSERT_REGISTERS(0x9C, 0, 0, 0, 0, 0b01100000, 0x12, 0x34, 0, 2);
    REQUIRE(ticks() == 16);
    REQUIRE(mem(0x1234) == 0x0F);

    regs().a = 0xAB;
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0xCC;
    runOp(0x96);
    ASSERT_REGISTERS(0xDF, 0, 0, 0, 0, 0b01110000, 0x12, 0x34, 0, 3);
    REQUIRE(ticks() == 24);
    REQUIRE(mem(0x1234) == 0xCC);

    regs().a = 0xAB;
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0xAB;
    runOp(0x96);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b11000000, 0x12, 0x34, 0, 4);
    REQUIRE(ticks() == 32);
    REQUIRE(mem(0x1234) == 0xAB);
}