#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xF0", "[cpu_ops_ldh_a_imm8]")
{
    mem(0x01) = 0x12;
    mem(0xFF12) = 0xAB;

    runOp(0xF0);

    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x02);
}