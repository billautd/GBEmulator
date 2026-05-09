#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x34", "[cpu_ops_inc_hl]")
{
    // Byte pointed to
    regs().h = 0xAB;
    regs().l = 0xCD;

    mem(0xABCD) = 0x12;
    runOp(0x34);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0xAB, 0xCD, 0, 1);
    REQUIRE(mem(0xABCD) == 0x13);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0xFF;
    runOp(0x34);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0);
    REQUIRE(ticks() == 24);

    mem(0xABCD) = 0x0F;
    runOp(0x34);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0xAB, 0xCD, 0, 3);
    REQUIRE(mem(0xABCD) == 0x10);
    REQUIRE(ticks() == 36);
}