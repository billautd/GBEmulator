#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xC1", "[cpu_ops_pop_r16stk]")
{
    regs().sp = 0xCFFD;
    mem(0xCFFD) = 0xAB;
    mem(0xCFFE) = 0xCD;

    runOp(0xC1);
    ASSERT_REGISTERS(0, 0xCD, 0xAB, 0, 0, 0, 0, 0, 0, 0xCFFF, 1);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xD1", "[cpu_ops_pop_r16stk]")
{
    regs().sp = 0xCFFD;
    mem(0xCFFD) = 0xAB;
    mem(0xCFFE) = 0xCD;

    runOp(0xD1);
    ASSERT_REGISTERS(0, 0, 0, 0xCD, 0xAB, 0, 0, 0, 0, 0xCFFF, 1);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xE1", "[cpu_ops_pop_r16stk]")
{
    regs().sp = 0xCFFD;
    mem(0xCFFD) = 0xAB;
    mem(0xCFFE) = 0xCD;

    runOp(0xE1);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xCD, 0xAB, 0xCFFF, 1);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xF1", "[cpu_ops_pop_r16stk]")
{
    regs().sp = 0xCFFD;
    mem(0xCFFD) = 0xAB;
    mem(0xCFFE) = 0xCD;

    runOp(0xF1);
    ASSERT_REGISTERS(0xCD, 0, 0, 0, 0, 0xAB, 0, 0, 0, 0xCFFF, 1);
}