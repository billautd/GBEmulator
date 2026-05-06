#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCE", "[cpu_ops_adc_a_imm8]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    mem(0x01) = 0x10;
    runOp(0xCE);
    ASSERT_REGISTERS(0xBC, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 2);
    REQUIRE(mem(0x01) == 0x10);
    REQUIRE(ticks() == 8);

    regs().a = 0xFE;
    regs().f = 0b00010000;
    mem(0x03) = 0x01;
    runOp(0xCE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10110000, 0, 0, 0, 0, 4);
    REQUIRE(mem(0x03) == 0x01);
    REQUIRE(ticks() == 16);

    regs().a = 0x0E;
    regs().f = 0b00010000;
    mem(0x05) = 0x01;
    runOp(0xCE);
    ASSERT_REGISTERS(0x10, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 6);
    REQUIRE(mem(0x05) == 0x01);
    REQUIRE(ticks() == 24);

    regs().a = 0x0E;
    regs().f = 0b00000000;
    mem(0x07) = 0x01;
    runOp(0xCE);
    ASSERT_REGISTERS(0x0F, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 8);
    REQUIRE(mem(0x07) == 0x01);
    REQUIRE(ticks() == 32);
}