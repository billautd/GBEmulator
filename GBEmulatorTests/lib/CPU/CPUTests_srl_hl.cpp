#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB3E", "[cpu_ops_srl_hl]")
{
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0b11000011;
    runCBPrefixOp(0x3E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0x12, 0x34, 0, 2);
    REQUIRE(mem(0x1234) == 0b01100001);
    REQUIRE(ticks() == 16);

    mem(0x1234) = 0;
    runCBPrefixOp(0x3E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0x12, 0x34, 0, 4);
    REQUIRE(mem(0x1234) == 0);
    REQUIRE(ticks() == 32);

    mem(0x1234) = 0b01110000;
    runCBPrefixOp(0x3E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0x12, 0x34, 0, 6);
    REQUIRE(mem(0x1234) == 0b00111000);
    REQUIRE(ticks() == 48);
}