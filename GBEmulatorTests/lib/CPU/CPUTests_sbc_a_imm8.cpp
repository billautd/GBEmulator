#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xDE", "[cpu_ops_sbc_a_imm8]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    mem(0x01) = 0x01;
    runOp(0xDE);
    ASSERT_REGISTERS(0xA9, 0, 0, 0, 0, 0b01000000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
    REQUIRE(mem(0x01) == 0x01);

    regs().a = 0xAB;
    regs().f = 0b00010000;
    mem(0x03) = 0x0F;
    runOp(0xDE);
    ASSERT_REGISTERS(0x9B, 0, 0, 0, 0, 0b01100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
    REQUIRE(mem(0x03) == 0x0F);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    mem(0x05) = 0xCC;
    runOp(0xDE);
    ASSERT_REGISTERS(0xDF, 0, 0, 0, 0, 0b01110000, 0, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
    REQUIRE(mem(0x05) == 0xCC);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    mem(0x07) = 0xAB;
    runOp(0xDE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b11000000, 0, 0, 0, 0, 8);
    REQUIRE(ticks() == 32);
    REQUIRE(mem(0x07) == 0xAB);
}