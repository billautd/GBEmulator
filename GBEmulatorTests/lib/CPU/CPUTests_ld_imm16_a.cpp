#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xEA", "[cpu_ops_ld_imm16_a]")
{
    // Value to copy
    regs().a = 0xEF;
    // Byte pointed to
    mem(0x01) = 0xAB;
    mem(0x02) = 0xCD;

    runOp(0xEA);

    ASSERT_REGISTERS(0xEF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3);
    REQUIRE(mem(0xCDAB) == 0xEF);
}