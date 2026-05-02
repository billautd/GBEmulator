#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xFB", "[cpu_ops_ei]")
{
    cpu().getInterrupts().setIME(true);
    runOp(0xFB);
    REQUIRE(cpu().getInterrupts().isIME());
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);

    cpu().getInterrupts().setIME(false);
    runOp(0xFB);
    REQUIRE(cpu().getInterrupts().isIME());
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x02);
    REQUIRE(ticks() == 8);
}