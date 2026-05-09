#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xF6", "[cpu_ops_or_n]")
{
    regs().a = 0xAB;
    mem(0x01) = 0xCD;
    runOp(0xF6);
    ASSERT_REGISTERS(0xEF, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 2);
    REQUIRE(mem(0x01) == 0xCD);
    REQUIRE(ticks() == 8);

    regs().a = 0;
    mem(0x03) = 0;
    runOp(0xF6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(mem(0x03) == 0);
    REQUIRE(ticks() == 16);
}