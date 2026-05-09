#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xEE", "[cpu_ops_xor_n]")
{
    regs().a = 0xAB;
    mem(0x01) = 0xCD;
    runOp(0xEE);
    ASSERT_REGISTERS(0b01100110, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 2);
    REQUIRE(mem(0x01) == 0xCD);
    REQUIRE(ticks() == 8);

    regs().a = 0xFF;
    mem(0x03) = 0xFF;
    runOp(0xEE);
    ASSERT_REGISTERS(0x00, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(mem(0x03) == 0xFF);
    REQUIRE(ticks() == 16);
}