#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x04", "[cpu_ops_inc_r8]")
{
    regs().b = 0x12;
    runOp(0x04);
    ASSERT_REGISTERS(0, 0x13, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().b = 0xFF;
    runOp(0x04);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0x0F;
    runOp(0x04);
    ASSERT_REGISTERS(0, 0x10, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x0C", "[cpu_ops_inc_r8]")
{
    regs().c = 0x12;
    runOp(0x0C);
    ASSERT_REGISTERS(0, 0, 0x13, 0, 0, 0b00000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().c = 0xFF;
    runOp(0x0C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0x0F;
    runOp(0x0C);
    ASSERT_REGISTERS(0, 0, 0x10, 0, 0, 0b00100000, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x14", "[cpu_ops_inc_r8]")
{
    regs().d = 0x12;
    runOp(0x14);
    ASSERT_REGISTERS(0, 0, 0, 0x13, 0, 0b00000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().d = 0xFF;
    runOp(0x14);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0x0F;
    runOp(0x14);
    ASSERT_REGISTERS(0, 0, 0, 0x10, 0, 0b00100000, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x1C", "[cpu_ops_inc_r8]")
{
    regs().e = 0x12;
    runOp(0x1C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x13, 0b00000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().e = 0xFF;
    runOp(0x1C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0x0F;
    runOp(0x1C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x10, 0b00100000, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x24", "[cpu_ops_inc_r8]")
{
    regs().h = 0x12;
    runOp(0x24);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0x13, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().h = 0xFF;
    runOp(0x24);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0x0F;
    runOp(0x24);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0x10, 0, 0, 3);
    REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x2C", "[cpu_ops_inc_r8]")
{
    regs().l = 0x12;
    runOp(0x2C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0x13, 0, 1);
    REQUIRE(ticks() == 4);

    regs().l = 0xFF;
    runOp(0x2C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0x0F;
    runOp(0x2C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0, 0x10, 0, 3);
    REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x34", "[cpu_ops_inc_r8]")
{
    // Byte pointed to
    regs().h = 0xAB;
    regs().l = 0xCD;

    mem(0xABCD) = 0x12;
    runOp(0x34);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0xAB, 0xCD, 0, 1);
    REQUIRE(mem(0xABCD) == 0x13);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0xFF;
    runOp(0x34);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0);
    REQUIRE(ticks() == 24);

    mem(0xABCD) = 0x0F;
    runOp(0x34);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0xAB, 0xCD, 0, 3);
    REQUIRE(mem(0xABCD) == 0x10);
    REQUIRE(ticks() == 36);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x3C", "[cpu_ops_inc_r8]")
{
    regs().a = 0x12;
    runOp(0x3C);
    ASSERT_REGISTERS(0x13, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    runOp(0x3C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x0F;
    runOp(0x3C);
    ASSERT_REGISTERS(0x10, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);
}