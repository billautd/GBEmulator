#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xF3", "[cpu_ops_di]")
{
    cpu().getInterrupts().setIME(false);
    runOp(0xF3);
    REQUIRE_FALSE(cpu().getInterrupts().isIME());
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);

    cpu().getInterrupts().setIME(true);
    runOp(0xF3);
    REQUIRE_FALSE(cpu().getInterrupts().isIME());
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x02);
    REQUIRE(ticks() == 8);
}