#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xC2", "[cpu_ops_jp_cond_imm16]")
{
    // Z -> Do not jump
    regs().pc = 0x100;
    regs().f = 0b10000000;

    mem(0x101) = 0xAB;
    mem(0x102) = 0xCD;
    runOp(0xC2);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 0x103);

    // NZ -> Jump
    regs().pc = 0x200;
    regs().f = 0b00000000;
    mem(0x201) = 0xAB;
    mem(0x202) = 0xCD;
    runOp(0xC2);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 0xCDAB);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCA", "[cpu_ops_jp_cond_imm16]")
{
    // NZ -> Do not jump
    regs().pc = 0x100;
    regs().f = 0b00000000;

    mem(0x101) = 0xAB;
    mem(0x102) = 0xCD;
    runOp(0xCA);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 0x103);

    // Z -> Jump
    regs().pc = 0x200;
    regs().f = 0b10000000;
    mem(0x201) = 0xAB;
    mem(0x202) = 0xCD;
    runOp(0xCA);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 0xCDAB);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xD2", "[cpu_ops_jp_cond_imm16]")
{
    // C -> Do not jump
    regs().pc = 0x100;
    regs().f = 0b00010000;

    mem(0x101) = 0xAB;
    mem(0x102) = 0xCD;
    runOp(0xD2);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 0, 0x103);

    // NC -> Jump
    regs().pc = 0x200;
    regs().f = 0b00000000;
    mem(0x201) = 0xAB;
    mem(0x202) = 0xCD;
    runOp(0xD2);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 0xCDAB);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xDA", "[cpu_ops_jp_cond_imm16]")
{
    // NC -> Do not jump
    regs().pc = 0x100;
    regs().f = 0b00000000;

    mem(0x101) = 0xAB;
    mem(0x102) = 0xCD;
    runOp(0xDA);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 0x103);

    // C -> Jump
    regs().pc = 0x200;
    regs().f = 0b00010000;
    mem(0x201) = 0xAB;
    mem(0x202) = 0xCD;
    runOp(0xDA);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 0, 0xCDAB);
}