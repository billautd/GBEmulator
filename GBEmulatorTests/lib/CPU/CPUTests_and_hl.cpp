#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xA6", "[cpu_ops_and_hl]")
{
    // Byte pointed to
    regs().h = 0xAB;
    regs().l = 0xCD;

    regs().a = 0xEF;
    mem(0xABCD) = 0x12;
    runOp(0xA6);
    ASSERT_REGISTERS(0x02, 0, 0, 0, 0, 0b00100000, 0xAB, 0xCD, 0, 1);
    REQUIRE(mem(0xABCD) == 0x12);
    REQUIRE(ticks() == 8);

    regs().a = 0x12;
    mem(0xABCD) = 0;
    runOp(0xA6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0);
    REQUIRE(ticks() == 16);
}