#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xF2", "[cpu_ops_ldh_a_c]")
{
    regs().a = 0;
    regs().c = 0x12;
    mem(0xFF12) = 0xAB;
    runOp(0xF2);

    ASSERT_REGISTERS(0xAB, 0, 0x12, 0, 0, 0, 0, 0, 0, 0, 1);
    REQUIRE(mem(0xFF12) == 0xAB);
    REQUIRE(ticks() == 8);
}