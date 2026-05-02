#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xC6", "[cpu_ops_add_a_imm8]")
{
    regs().a = 0xAB;
    mem(0x01) = 0x10;
    runOp(0xC6);
    ASSERT_REGISTERS(0xBB, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 2);
    REQUIRE(mem(0x01) == 0x10);
    REQUIRE(ticks() == 8);

    regs().a = 0xFF;
    mem(0x03) = 0x01;
    runOp(0xC6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10110000, 0, 0, 0, 0, 4);
    REQUIRE(mem(0x03) == 0x01);
    REQUIRE(ticks() == 16);

    regs().a = 0x0F;
    mem(0x05) = 0x01;
    runOp(0xC6);
    ASSERT_REGISTERS(0x10, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 6);
    REQUIRE(mem(0x05) == 0x01);
    REQUIRE(ticks() == 24);
}