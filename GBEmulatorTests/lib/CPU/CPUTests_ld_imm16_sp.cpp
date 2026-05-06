#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x08", "[cpu_ops_ld_imm16_sp]")
{
    // Value to copy
    regs().sp = 0x1234;
    // Byte pointed to
    mem(0x01) = 0xAB;
    mem(0x02) = 0xCD;

    runOp(0x08);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1234, 3);
    REQUIRE(mem(0xCDAB) == 0x34);
    REQUIRE(mem(0xCDAC) == 0x12);
    REQUIRE(ticks() == 20);
}