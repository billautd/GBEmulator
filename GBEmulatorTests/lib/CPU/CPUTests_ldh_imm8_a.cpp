#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xE0", "[cpu_ops_ldh_imm8_a]")
{
    regs().a = 0xAB;
    mem(0x01) = 0x12;

    runOp(0xE0);

    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x02);
    REQUIRE(mem(0xFF12) == 0xAB);
    REQUIRE(ticks() == 12);
}