#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x86", "[cpu_ops_add_hl]")
{
    // Byte pointed to
    regs().h = 0xAB;
    regs().l = 0xCD;

    regs().a = 0xAB;
    mem(0xABCD) = 0x10;
    runOp(0x86);
    ASSERT_REGISTERS(0xBB, 0, 0, 0, 0, 0b00000000, 0xAB, 0xCD, 0, 1);
    REQUIRE(mem(0xABCD) == 0x10);
    REQUIRE(ticks() == 8);

    regs().a = 0xFF;
    mem(0xABCD) = 0x01;
    runOp(0x86);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10110000, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0x01);
    REQUIRE(ticks() == 16);

    regs().a = 0x0F;
    mem(0xABCD) = 0x01;
    runOp(0x86);
    ASSERT_REGISTERS(0x10, 0, 0, 0, 0, 0b00100000, 0xAB, 0xCD, 0, 3);
    REQUIRE(mem(0xABCD) == 0x01);
    REQUIRE(ticks() == 24);
}