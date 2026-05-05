#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xC4", "[cpu_ops_call_cond_imm16]")
{
    // Z -> Do not jump
    regs().sp = 0xCFFF;
    regs().pc = 0x100;
    regs().f = 0b10000000;

    mem(0x101) = 0xAB;
    mem(0x102) = 0xCD;
    runOp(0xC4);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0xCFFF, 0x103);
    REQUIRE(ticks() == 12);

    // NZ -> Jump
    regs().sp = 0xCFFF;
    regs().pc = 0x200;
    regs().f = 0b00000000;
    mem(0x201) = 0xAB;
    mem(0x202) = 0xCD;
    runOp(0xC4);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0xCFFD, 0xCDAB);
    REQUIRE(mem(0xCFFD) == 0x03);
    REQUIRE(mem(0xCFFE) == 0x02);
    REQUIRE(ticks() == 36);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCC", "[cpu_ops_call_cond_imm16]")
{
    // NZ -> Do not jump
    regs().sp = 0xCFFF;
    regs().pc = 0x100;
    regs().f = 0b00000000;

    mem(0x101) = 0xAB;
    mem(0x102) = 0xCD;
    runOp(0xCC);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0xCFFF, 0x103);
    REQUIRE(ticks() == 12);

    // Z -> Jump
    regs().sp = 0xCFFF;
    regs().pc = 0x200;
    regs().f = 0b10000000;
    mem(0x201) = 0xAB;
    mem(0x202) = 0xCD;
    runOp(0xCC);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0xCFFD, 0xCDAB);
    REQUIRE(mem(0xCFFD) == 0x03);
    REQUIRE(mem(0xCFFE) == 0x02);
    REQUIRE(ticks() == 36);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xD4", "[cpu_ops_call_cond_imm16]")
{
    // C -> Do not jump
    regs().sp = 0xCFFF;
    regs().pc = 0x100;
    regs().f = 0b00010000;

    mem(0x101) = 0xAB;
    mem(0x102) = 0xCD;
    runOp(0xD4);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 0xCFFF, 0x103);
    REQUIRE(ticks() == 12);

    // NC -> Jump
    regs().sp = 0xCFFF;
    regs().pc = 0x200;
    regs().f = 0b00000000;
    mem(0x201) = 0xAB;
    mem(0x202) = 0xCD;
    runOp(0xD4);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0xCFFD, 0xCDAB);
    REQUIRE(mem(0xCFFD) == 0x03);
    REQUIRE(mem(0xCFFE) == 0x02);
    REQUIRE(ticks() == 36);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xDC", "[cpu_ops_call_cond_imm16]")
{
    // NC -> Do not jump
    regs().sp = 0xCFFF;
    regs().pc = 0x100;
    regs().f = 0b00000000;

    mem(0x101) = 0xAB;
    mem(0x102) = 0xCD;
    runOp(0xDC);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0xCFFF, 0x103);
    REQUIRE(ticks() == 12);

    // C -> Jump
    regs().sp = 0xCFFF;
    regs().pc = 0x200;
    regs().f = 0b00010000;
    mem(0x201) = 0xAB;
    mem(0x202) = 0xCD;
    runOp(0xDC);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 0xCFFD, 0xCDAB);
    REQUIRE(mem(0xCFFD) == 0x03);
    REQUIRE(mem(0xCFFE) == 0x02);
    REQUIRE(ticks() == 36);
}