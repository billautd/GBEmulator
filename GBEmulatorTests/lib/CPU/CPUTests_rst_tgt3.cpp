#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xC7", "[cpu_ops_rst_tgt3]")
{
    regs().sp = 0xCFFF;
    regs().pc = 0x100;

    runOp(0xC7);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0xCFFD, 0);
    // Store pointer after original function call
    REQUIRE(mem(0xCFFD) == 0x01);
    REQUIRE(mem(0xCFFE) == 0x01);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCF", "[cpu_ops_rst_tgt3]")
{
    regs().sp = 0xCFFF;
    regs().pc = 0x100;

    runOp(0xCF);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0xCFFD, 0x08);
    // Store pointer after original function call
    REQUIRE(mem(0xCFFD) == 0x01);
    REQUIRE(mem(0xCFFE) == 0x01);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xD7", "[cpu_ops_rst_tgt3]")
{
    regs().sp = 0xCFFF;
    regs().pc = 0x100;

    runOp(0xD7);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0xCFFD, 0x10);
    // Store pointer after original function call
    REQUIRE(mem(0xCFFD) == 0x01);
    REQUIRE(mem(0xCFFE) == 0x01);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xDF", "[cpu_ops_rst_tgt3]")
{
    regs().sp = 0xCFFF;
    regs().pc = 0x100;

    runOp(0xDF);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0xCFFD, 0x18);
    // Store pointer after original function call
    REQUIRE(mem(0xCFFD) == 0x01);
    REQUIRE(mem(0xCFFE) == 0x01);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xE7", "[cpu_ops_rst_tgt3]")
{
    regs().sp = 0xCFFF;
    regs().pc = 0x100;

    runOp(0xE7);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0xCFFD, 0x20);
    // Store pointer after original function call
    REQUIRE(mem(0xCFFD) == 0x01);
    REQUIRE(mem(0xCFFE) == 0x01);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xEF", "[cpu_ops_rst_tgt3]")
{
    regs().sp = 0xCFFF;
    regs().pc = 0x100;

    runOp(0xEF);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0xCFFD, 0x28);
    // Store pointer after original function call
    REQUIRE(mem(0xCFFD) == 0x01);
    REQUIRE(mem(0xCFFE) == 0x01);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xF7", "[cpu_ops_rst_tgt3]")
{
    regs().sp = 0xCFFF;
    regs().pc = 0x100;

    runOp(0xF7);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0xCFFD, 0x30);
    // Store pointer after original function call
    REQUIRE(mem(0xCFFD) == 0x01);
    REQUIRE(mem(0xCFFE) == 0x01);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xFF", "[cpu_ops_rst_tgt3]")
{
    regs().sp = 0xCFFF;
    regs().pc = 0x100;

    runOp(0xFF);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0xCFFD, 0x38);
    // Store pointer after original function call
    REQUIRE(mem(0xCFFD) == 0x01);
    REQUIRE(mem(0xCFFE) == 0x01);
    REQUIRE(ticks() == 16);
}