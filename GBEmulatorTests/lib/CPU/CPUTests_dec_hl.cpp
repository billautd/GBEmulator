#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x35", "[cpu_ops_dec_hl]")
{
    // Byte pointed to
    regs().h = 0xAB;
    regs().l = 0xCD;

    mem(0xABCD) = 0x12;
    runOp(0x35);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b01000000, 0xAB, 0xCD, 0, 1);
    REQUIRE(mem(0xABCD) == 0x11);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0x00;
    runOp(0x35);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b01100000, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0xFF);
    REQUIRE(ticks() == 24);

    mem(0xABCD) = 0xA0;
    runOp(0x35);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b01100000, 0xAB, 0xCD, 0, 3);
    REQUIRE(mem(0xABCD) == 0x9F);
    REQUIRE(ticks() == 36);

    mem(0xABCD) = 0x01;
    runOp(0x35);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b11000000, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0x00);
    REQUIRE(ticks() == 48);
}