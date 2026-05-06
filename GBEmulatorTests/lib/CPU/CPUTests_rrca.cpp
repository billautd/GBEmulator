#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x0F", "[cpu_ops_rrca]")
{
    regs().a = 0b11000011;
    regs().f = 0b00010000;

    runOp(0x0F);

    ASSERT_REGISTERS(0b11100001, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0b01000011;
    regs().f = 0b00010000;

    runOp(0x0F);

    ASSERT_REGISTERS(0b10100001, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01100010;
    regs().f = 0b00000000;

    runOp(0x0F);

    ASSERT_REGISTERS(0b00110001, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);
}