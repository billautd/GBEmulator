#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xD6", "[cpu_ops_sub_a_imm8]")
{
    regs().a = 0xAB;
    mem(0x01) = 0x01;
    runOp(0xD6);
    ASSERT_REGISTERS(0xAA, 0, 0, 0, 0, 0b01000000, 0, 0, 0, 0, 0x02);
    REQUIRE(ticks() == 8);

    regs().a = 0xAB;
    mem(0x03) = 0x0F;
    runOp(0xD6);
    ASSERT_REGISTERS(0x9C, 0, 0, 0, 0, 0b01100000, 0, 0, 0, 0, 0x04);
    REQUIRE(ticks() == 16);

    regs().a = 0xAB;
    mem(0x05) = 0xCC;
    runOp(0xD6);
    ASSERT_REGISTERS(0xDF, 0, 0, 0, 0, 0b01110000, 0, 0, 0, 0, 0x06);
    REQUIRE(ticks() == 24);

    regs().a = 0xAB;
    mem(0x07) = 0xAB;
    runOp(0xD6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b11000000, 0, 0, 0, 0, 0x08);
    REQUIRE(ticks() == 32);
}