#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCD", "[cpu_ops_call_nn]")
{
    regs().sp = 0xCFFF;
    regs().pc = 0x100;
    mem(0x101) = 0xAB;
    mem(0x102) = 0xCD;

    runOp(0xCD);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0xCFFD, 0xCDAB);
    // Store pointer after original function call
    REQUIRE(mem(0xCFFD) == 0x03);
    REQUIRE(mem(0xCFFE) == 0x01);
    REQUIRE(ticks() == 24);
}