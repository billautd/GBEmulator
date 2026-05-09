#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xB6", "[cpu_ops_or_hl]")
{
    // Byte pointed to
    regs().h = 0xAB;
    regs().l = 0xCD;

    regs().a = 0xEF;
    mem(0xABCD) = 0x12;
    runOp(0xB6);
    ASSERT_REGISTERS(0xFF, 0, 0, 0, 0, 0b00000000, 0xAB, 0xCD, 0, 1);
    REQUIRE(mem(0xABCD) == 0x12);
    REQUIRE(ticks() == 8);

    regs().a = 0;
    mem(0xABCD) = 0;
    runOp(0xB6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0);
    REQUIRE(ticks() == 16);
}