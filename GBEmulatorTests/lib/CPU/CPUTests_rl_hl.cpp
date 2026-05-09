#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB16", "[cpu_ops_rl_hl]")
{
    regs().h = 0x12;
    regs().l = 0x34;
    regs().f = 0b00010000;
    mem(0x1234) = 0b11000011;
    runCBPrefixOp(0x16);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0x12, 0x34, 0, 2);
    REQUIRE(mem(0x1234) == 0b10000111);
    REQUIRE(ticks() == 16);

    regs().f = 0b00000000;
    mem(0x1234) = 0b01000010;
    runCBPrefixOp(0x16);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0x12, 0x34, 0, 4);
    REQUIRE(mem(0x1234) == 0b10000100);
    REQUIRE(ticks() == 32);

    regs().f = 0b00000000;
    mem(0x1234) = 0;
    runCBPrefixOp(0x16);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0x12, 0x34, 0, 6);
    REQUIRE(mem(0x1234) == 0);
    REQUIRE(ticks() == 48);
}