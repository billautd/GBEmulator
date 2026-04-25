#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xC3", "[cpu_ops_jp_imm16]")
{
    mem(0x01) = 0xAB;
    mem(0x02) = 0xCD;
    runOp(0xC3);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xCDAB);
}