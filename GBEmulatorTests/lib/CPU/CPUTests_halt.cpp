#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x76", "[cpu_ops_halt]")
{
    cpu().setHalted(false);
    runOp(0x76);
    REQUIRE(cpu().isHalted());
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);

    // PC not increased
    cpu().setHalted(true);
    runOp(0x76);
    REQUIRE(cpu().isHalted());
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 8);
}