#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xE2", "[cpu_ops_ldh_c_a]")
{
    regs().a = 0xAB;
    regs().c = 0x12;
    runOp(0xE2);

    ASSERT_REGISTERS(0xAB, 0, 0x12, 0, 0, 0, 0, 0, 0, 1);
    REQUIRE(mem(0xFF12) == 0xAB);
    REQUIRE(ticks() == 8);
}