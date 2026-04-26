#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xE9", "[cpu_ops_jp_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    runOp(0xE9);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 0xABCD);
}