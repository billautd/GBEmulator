#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xBE", "[cpu_ops_cp_hl]")
{
    regs().a = 0xAB;
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0xAB;
    runOp(0xBE);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b11000000, 0x12, 0x34, 0, 1);
    REQUIRE(mem(0x1234) == 0xAB);
    REQUIRE(ticks() == 8);

    mem(0x1234) = 0x12;
    runOp(0xBE);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b01000000, 0x12, 0x34, 0, 2);
    REQUIRE(mem(0x1234) == 0x12);
    REQUIRE(ticks() == 16);

    mem(0x1234) = 0x99;
    runOp(0xBE);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b01000000, 0x12, 0x34, 0, 3);
    REQUIRE(mem(0x1234) == 0x99);
    REQUIRE(ticks() == 24);

    mem(0x1234) = 0xFF;
    runOp(0xBE);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b01110000, 0x12, 0x34, 0, 4);
    REQUIRE(mem(0x1234) == 0xFF);
    REQUIRE(ticks() == 32);
}