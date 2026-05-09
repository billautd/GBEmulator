#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x18", "[cpu_ops_jr_e]")
{
    regs().pc = 0x100;
    // Value is negative
    mem(0x101) = 0xAB;
    runOp(0x18);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0x102 + (i8)0xAB);
    REQUIRE(ticks() == 12);

    // NZ -> Jump
    regs().pc = 0x200;
    // Value is positive
    mem(0x201) = 0x06;
    runOp(0x18);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0x202 + (i8)0x06);
    REQUIRE(ticks() == 24);
}