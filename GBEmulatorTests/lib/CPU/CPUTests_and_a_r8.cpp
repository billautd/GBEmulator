#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xA0", "[cpu_ops_and_a_r8]")
{
    regs().a = 0xAB;
    regs().b = 0xCD;
    runOp(0xA0);
    ASSERT_REGISTERS(0x89, 0xCD, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().b = 0;
    runOp(0xA0);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xA1", "[cpu_ops_and_a_r8]")
{
    regs().a = 0xAB;
    regs().c = 0xCD;
    runOp(0xA1);
    ASSERT_REGISTERS(0x89, 0, 0xCD, 0, 0, 0b00100000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().c = 0;
    runOp(0xA1);
    ASSERT_REGISTERS(0x00, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xA2", "[cpu_ops_and_a_r8]")
{
    regs().a = 0xAB;
    regs().d = 0xCD;
    runOp(0xA2);
    ASSERT_REGISTERS(0x89, 0, 0, 0xCD, 0, 0b00100000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().d = 0;
    runOp(0xA2);
    ASSERT_REGISTERS(0x00, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xA3", "[cpu_ops_and_a_r8]")
{
    regs().a = 0xAB;
    regs().e = 0xCD;
    runOp(0xA3);
    ASSERT_REGISTERS(0x89, 0, 0, 0, 0xCD, 0b00100000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().e = 0;
    runOp(0xA3);
    ASSERT_REGISTERS(0x00, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xA4", "[cpu_ops_and_a_r8]")
{
    regs().a = 0xAB;
    regs().h = 0xCD;
    runOp(0xA4);
    ASSERT_REGISTERS(0x89, 0, 0, 0, 0, 0b00100000, 0, 0xCD, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().h = 0;
    runOp(0xA4);
    ASSERT_REGISTERS(0x00, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xA5", "[cpu_ops_and_a_r8]")
{
    regs().a = 0xAB;
    regs().l = 0xCD;
    runOp(0xA5);
    ASSERT_REGISTERS(0x89, 0, 0, 0, 0, 0b00100000, 0, 0, 0xCD, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().l = 0;
    runOp(0xA5);
    ASSERT_REGISTERS(0x00, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xA6", "[cpu_ops_and_a_r8]")
{
    // Byte pointed to
    regs().h = 0xAB;
    regs().l = 0xCD;

    regs().a = 0xEF;
    mem(0xABCD) = 0x12;
    runOp(0xA6);
    ASSERT_REGISTERS(0x02, 0, 0, 0, 0, 0b00100000, 0, 0xAB, 0xCD, 0, 1);
    REQUIRE(mem(0xABCD) == 0x12);
    REQUIRE(ticks() == 8);

    regs().a = 0x12;
    mem(0xABCD) = 0;
    runOp(0xA6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xA7", "[cpu_ops_and_a_r8]")
{
    regs().a = 0xAB;
    runOp(0xA7);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0;
    runOp(0xA7);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}