#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xE6", "[cpu_ops_and_a_imm8]")
{
    regs().a = 0xAB;
    mem(0x01) = 0xAB;
    runOp(0xE6);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 0x02);
    REQUIRE(ticks() == 8);

    mem(0x03) = 0x12;
    runOp(0xE6);
    ASSERT_REGISTERS(0x02, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 0x04);
    REQUIRE(ticks() == 16);

    mem(0x05) = 0xFD;
    runOp(0xE6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 0x06);
    REQUIRE(ticks() == 24);
}