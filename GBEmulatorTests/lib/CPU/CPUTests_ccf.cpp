#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x3F", "[cpu_ops_ccf]")
{
    regs().f = 0b11110000;
    runOp(0x3F);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().f = 0b00010000;

    runOp(0x3F);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}