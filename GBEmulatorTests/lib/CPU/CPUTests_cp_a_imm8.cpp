#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xFE", "[cpu_ops_cp_a_imm8]")
{
    regs().a = 0xAB;
    mem(0x01) = 0xAB;
    runOp(0xFE);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b11000000, 0, 0, 0, 0, 0x02);
    REQUIRE(ticks() == 8);

    mem(0x03) = 0x12;
    runOp(0xFE);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b01000000, 0, 0, 0, 0, 0x04);
    REQUIRE(ticks() == 16);

    mem(0x05) = 0x99;
    runOp(0xFE);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b01000000, 0, 0, 0, 0, 0x06);
    REQUIRE(ticks() == 24);

    mem(0x07) = 0xFF;
    runOp(0xFE);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b01110000, 0, 0, 0, 0, 0x08);
    REQUIRE(ticks() == 32);
}