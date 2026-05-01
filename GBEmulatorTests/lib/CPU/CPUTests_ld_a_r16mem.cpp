#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x0A", "[cpu_ops_ld_a_r16mem]")
{
    // Value to copy
    mem(0xABCD) = 0xEF;
    // Byte pointed to
    regs().b = 0xAB;
    regs().c = 0xCD;

    runOp(0x0A);

    ASSERT_REGISTERS(0xEF, 0xAB, 0xCD, 0, 0, 0, 0, 0, 0, 0, 1);
    REQUIRE(mem(0xABCD) == 0xEF);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x1A", "[cpu_ops_ld_a_r16mem]")
{
    // Value to copy
    mem(0xABCD) = 0xEF;
    // Byte pointed to
    regs().d = 0xAB;
    regs().e = 0xCD;

    runOp(0x1A);

    ASSERT_REGISTERS(0xEF, 0, 0, 0xAB, 0xCD, 0, 0, 0, 0, 0, 1);
    REQUIRE(mem(0xABCD) == 0xEF);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x2A", "[cpu_ops_ld_a_r16mem]")
{
    // Value to copy
    mem(0xABCD) = 0xEF;
    // Byte pointed to
    regs().h = 0xAB;
    regs().l = 0xCD;

    runOp(0x2A);

    ASSERT_REGISTERS(0xEF, 0, 0, 0, 0, 0, 0, 0xAB, 0xCE, 0, 1);
    REQUIRE(mem(0xABCD) == 0xEF);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x3A", "[cpu_ops_ld_a_r16mem]")
{
    // Value to copy
    mem(0xABCD) = 0xEF;
    // Byte pointed to
    regs().h = 0xAB;
    regs().l = 0xCD;

    runOp(0x3A);

    ASSERT_REGISTERS(0xEF, 0, 0, 0, 0, 0, 0, 0xAB, 0xCC, 0, 1);
    REQUIRE(mem(0xABCD) == 0xEF);
    REQUIRE(ticks() == 8);
}