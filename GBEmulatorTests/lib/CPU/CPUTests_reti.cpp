#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xD9", "[cpu_ops_reti]")
{
    regs().sp = 0xCFFD;
    mem(0xCFFD) = 0x12;
    mem(0xCFFE) = 0x34;
    cpu().getInterrupts().setIME(false);

    runOp(0xD9);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0xCFFF, 0x3412);
    REQUIRE(ticks() == 16);
    REQUIRE(cpu().getInterrupts().isEnablingIME());
}