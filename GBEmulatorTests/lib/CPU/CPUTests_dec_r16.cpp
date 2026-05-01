#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x0B", "[cpu_ops_dec_r16]")
{
    regs().b = 0x12;
    regs().c = 0x34;

    runOp(0x0B);

    ASSERT_REGISTERS(0, 0x12, 0x33, 0, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 8);

    regs().b = 0;
    regs().c = 0;

    runOp(0x0B);

    ASSERT_REGISTERS(0, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0x02);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x1B", "[cpu_ops_dec_r16]")
{
    regs().d = 0x12;
    regs().e = 0x34;

    runOp(0x1B);

    ASSERT_REGISTERS(0, 0, 0, 0x12, 0x33, 0, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 8);

    regs().d = 0;
    regs().e = 0;

    runOp(0x1B);

    ASSERT_REGISTERS(0, 0, 0, 0xFF, 0xFF, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x2B", "[cpu_ops_dec_r16]")
{
    regs().h = 0x12;
    regs().l = 0x34;

    runOp(0x2B);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0x12, 0x33, 0, 1);
    REQUIRE(ticks() == 8);

    regs().h = 0;
    regs().l = 0;

    runOp(0x2B);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xFF, 0xFF, 0, 2);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x3B", "[cpu_ops_dec_r16]")
{
    regs().sp = 0x1234;

    runOp(0x3B);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1233, 1);
    REQUIRE(ticks() == 8);

    regs().sp = 0;

    runOp(0x3B);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFF, 2);
    REQUIRE(ticks() == 16);
}