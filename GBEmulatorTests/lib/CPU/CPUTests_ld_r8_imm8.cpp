#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x06", "[cpu_ops_ld_r8_imm8]")
{
    mem(0x01) = 0xAB;
    runOp(0x06);
    ASSERT_REGISTERS(0, 0xAB, 0, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x0E", "[cpu_ops_ld_r8_imm8]")
{
    mem(0x01) = 0xAB;
    runOp(0x0E);
    ASSERT_REGISTERS(0, 0, 0xAB, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x16", "[cpu_ops_ld_r8_imm8]")
{
    mem(0x01) = 0xAB;
    runOp(0x16);
    ASSERT_REGISTERS(0, 0, 0, 0xAB, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x1E", "[cpu_ops_ld_r8_imm8]")
{
    mem(0x01) = 0xAB;
    runOp(0x1E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0xAB, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x26", "[cpu_ops_ld_r8_imm8]")
{
    mem(0x01) = 0xAB;
    runOp(0x26);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x2E", "[cpu_ops_ld_r8_imm8]")
{
    mem(0x01) = 0xAB;
    runOp(0x2E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0xAB, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x36", "[cpu_ops_ld_r8_imm8]")
{
    // Byte pointed to
    regs().h = 0x12;
    regs().l = 0x34;

    mem(0x01) = 0xAB;
    runOp(0x36);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0x12, 0x34, 0, 2);
    REQUIRE(mem(0x1234) == 0xAB);
    REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x3E", "[cpu_ops_ld_r8_imm8]")
{
    mem(0x01) = 0xAB;
    runOp(0x3E);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}