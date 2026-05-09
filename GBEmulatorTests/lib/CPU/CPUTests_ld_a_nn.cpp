#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xFA", "[cpu_ops_ld_a_nn]")
{
    // Value to copy
    mem(0xCDAB) = 0xEF;
    // Byte pointed to
    mem(0x01) = 0xAB;
    mem(0x02) = 0xCD;

    runOp(0xFA);

    ASSERT_REGISTERS(0xEF, 0, 0, 0, 0, 0, 0, 0, 0, 3);
    REQUIRE(mem(0xCDAB) == 0xEF);
    REQUIRE(ticks() == 16);
}