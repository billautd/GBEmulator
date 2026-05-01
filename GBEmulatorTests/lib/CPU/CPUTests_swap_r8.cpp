#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB30", "[cpu_ops_swap_r8]")
{
    regs().b = 0b11000011;
    runCBPrefixOp(0x30);
    ASSERT_REGISTERS(0, 0b00111100, 0, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0;
    runCBPrefixOp(0x30);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB31", "[cpu_ops_swap_r8]")
{
    regs().c = 0b11000011;
    runCBPrefixOp(0x31);
    ASSERT_REGISTERS(0, 0, 0b00111100, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0;
    runCBPrefixOp(0x31);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB32", "[cpu_ops_swap_r8]")
{
    regs().d = 0b11000011;
    runCBPrefixOp(0x32);
    ASSERT_REGISTERS(0, 0, 0, 0b00111100, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0;
    runCBPrefixOp(0x32);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB33", "[cpu_ops_swap_r8]")
{
    regs().e = 0b11000011;
    runCBPrefixOp(0x33);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b00111100, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0;
    runCBPrefixOp(0x33);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB34", "[cpu_ops_swap_r8]")
{
    regs().h = 0b11000011;
    runCBPrefixOp(0x34);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b00111100, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0;
    runCBPrefixOp(0x34);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB35", "[cpu_ops_swap_r8]")
{
    regs().l = 0b11000011;
    runCBPrefixOp(0x35);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b00111100, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0;
    runCBPrefixOp(0x35);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB36", "[cpu_ops_swap_r8]")
{
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0b11000011;
    runCBPrefixOp(0x36);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0x12, 0x34, 0, 2);
    REQUIRE(mem(0x1234) == 0b00111100);
    REQUIRE(ticks() == 16);

    mem(0x1234) = 0;
    runCBPrefixOp(0x36);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0x12, 0x34, 0, 4);
    REQUIRE(mem(0x1234) == 0);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB37", "[cpu_ops_swap_r8]")
{
    regs().a = 0b11000011;
    runCBPrefixOp(0x37);
    ASSERT_REGISTERS(0b00111100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0;
    runCBPrefixOp(0x37);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}