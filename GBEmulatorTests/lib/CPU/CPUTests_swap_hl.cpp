#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB36", "[cpu_ops_swap_hl]")
{
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0b11000011;
    runCBPrefixOp(0x36);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0x12, 0x34, 0, 2);
    REQUIRE(mem(0x1234) == 0b00111100);
    REQUIRE(ticks() == 16);

    mem(0x1234) = 0;
    runCBPrefixOp(0x36);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0x12, 0x34, 0, 4);
    REQUIRE(mem(0x1234) == 0);
    REQUIRE(ticks() == 32);
}