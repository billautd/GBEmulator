#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xC0", "[cpu_ops_ret_cond]")
{
    // Z -> Do not jump
    regs().pc = 0x100;
    regs().f = 0b10000000;

    regs().sp = 0xCFFD;
    mem(0xCFFD) = 0xAB;
    mem(0xCFFE) = 0xCD;
    runOp(0xC0);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0xCFFD, 0x101);
    REQUIRE(ticks() == 8);

    // NZ -> Jump
    regs().pc = 0x200;
    regs().f = 0b00000000;
    runOp(0xC0);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0xCFFF, 0xCDAB);
    REQUIRE(ticks() == 28);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xC8", "[cpu_ops_ret_cond]")
{
    // NZ -> Do not jump
    regs().pc = 0x100;
    regs().f = 0b00000000;

    regs().sp = 0xCFFD;
    mem(0xCFFD) = 0xAB;
    mem(0xCFFE) = 0xCD;
    runOp(0xC8);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0xCFFD, 0x101);
    REQUIRE(ticks() == 8);

    // NZ -> Jump
    regs().pc = 0x200;
    regs().f = 0b10000000;
    runOp(0xC8);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0xCFFF, 0xCDAB);
    REQUIRE(ticks() == 28);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xD0", "[cpu_ops_ret_cond]")
{
    // C -> Do not jump
    regs().pc = 0x100;
    regs().f = 0b00010000;

    regs().sp = 0xCFFD;
    mem(0xCFFD) = 0xAB;
    mem(0xCFFE) = 0xCD;
    runOp(0xD0);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 0xCFFD, 0x101);
    REQUIRE(ticks() == 8);

    // NC -> Jump
    regs().pc = 0x200;
    regs().f = 0b00000000;
    runOp(0xD0);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0xCFFF, 0xCDAB);
    REQUIRE(ticks() == 28);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xD8", "[cpu_ops_ret_cond]")
{
    // NC -> Do not jump
    regs().pc = 0x100;
    regs().f = 0b00000000;

    regs().sp = 0xCFFD;
    mem(0xCFFD) = 0xAB;
    mem(0xCFFE) = 0xCD;
    runOp(0xD8);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0xCFFD, 0x101);
    REQUIRE(ticks() == 8);

    // NZ -> Jump
    regs().pc = 0x200;
    regs().f = 0b00010000;
    runOp(0xD8);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 0xCFFF, 0xCDAB);
    REQUIRE(ticks() == 28);
}