#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xF8", "[cpu_ops_ld_hl_sp_e]")
{
    mem(0x01) = 0x0F;
    regs().sp = 0xABCD;

    runOp(0xF8);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0xAB, 0xDC, 0xABCD, 2);
    REQUIRE(mem(0x01) == 0x0F);
    REQUIRE(ticks() == 12);

    mem(0x03) = 0x81;
    regs().sp = 0xABCD;

    runOp(0xF8);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0xAB, 0x4E, 0xABCD, 4);
    REQUIRE(mem(0x03) == 0x81);
    REQUIRE(ticks() == 24);

    mem(0x05) = 0x0F;
    regs().sp = 0xABFE;

    runOp(0xF8);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00110000, 0xAC, 0x0D, 0xABFE, 6);
    REQUIRE(mem(0x05) == 0x0F);
    REQUIRE(ticks() == 36);
}