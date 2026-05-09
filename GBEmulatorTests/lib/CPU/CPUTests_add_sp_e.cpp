#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xE8", "[cpu_ops_add_sp_e]")
{
    mem(0x01) = 0x0F;
    regs().sp = 0xABCD;

    runOp(0xE8);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0, 0xABDC, 2);
    REQUIRE(mem(0x01) == 0x0F);
    REQUIRE(ticks() == 16);

    mem(0x03) = 0x81;
    regs().sp = 0xABCD;

    runOp(0xE8);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0, 0xAB4E, 4);
    REQUIRE(mem(0x03) == 0x81);
    REQUIRE(ticks() == 32);

    mem(0x05) = 0x0F;
    regs().sp = 0xABFE;

    runOp(0xE8);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00110000, 0, 0, 0xAC0D, 6);
    REQUIRE(mem(0x05) == 0x0F);
    REQUIRE(ticks() == 48);
}