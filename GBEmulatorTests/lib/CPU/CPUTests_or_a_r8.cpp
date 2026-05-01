#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xB0", "[cpu_ops_or_a_r8]")
{
    regs().a = 0xAB;
    regs().b = 0xCD;
    runOp(0xB0);
    ASSERT_REGISTERS(0xEF, 0xCD, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0;
    regs().b = 0;
    runOp(0xB0);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xB1", "[cpu_ops_or_a_r8]")
{
    regs().a = 0xAB;
    regs().c = 0xCD;
    runOp(0xB1);
    ASSERT_REGISTERS(0xEF, 0, 0xCD, 0, 0, 0b00000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0;
    regs().c = 0;
    runOp(0xB1);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xB2", "[cpu_ops_or_a_r8]")
{
    regs().a = 0xAB;
    regs().d = 0xCD;
    runOp(0xB2);
    ASSERT_REGISTERS(0xEF, 0, 0, 0xCD, 0, 0b00000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0;
    regs().d = 0;
    runOp(0xB2);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xB3", "[cpu_ops_or_a_r8]")
{
    regs().a = 0xAB;
    regs().e = 0xCD;
    runOp(0xB3);
    ASSERT_REGISTERS(0xEF, 0, 0, 0, 0xCD, 0b00000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0;
    regs().e = 0;
    runOp(0xB3);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xB4", "[cpu_ops_or_a_r8]")
{
    regs().a = 0xAB;
    regs().h = 0xCD;
    runOp(0xB4);
    ASSERT_REGISTERS(0xEF, 0, 0, 0, 0, 0b00000000, 0, 0xCD, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0;
    regs().h = 0;
    runOp(0xB4);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xB5", "[cpu_ops_or_a_r8]")
{
    regs().a = 0xAB;
    regs().l = 0xCD;
    runOp(0xB5);
    ASSERT_REGISTERS(0xEF, 0, 0, 0, 0, 0b00000000, 0, 0, 0xCD, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0;
    regs().l = 0;
    runOp(0xB5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xB6", "[cpu_ops_or_a_r8]")
{
    // Byte pointed to
    regs().h = 0xAB;
    regs().l = 0xCD;

    regs().a = 0xEF;
    mem(0xABCD) = 0x12;
    runOp(0xB6);
    ASSERT_REGISTERS(0xFF, 0, 0, 0, 0, 0b00000000, 0, 0xAB, 0xCD, 0, 1);
    REQUIRE(mem(0xABCD) == 0x12);
    REQUIRE(ticks() == 8);

    regs().a = 0;
    mem(0xABCD) = 0;
    runOp(0xB6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xB7", "[cpu_ops_or_a_r8]")
{
    regs().a = 0xAB;
    runOp(0xB7);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0;
    runOp(0xB7);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}