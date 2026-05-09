#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xC5", "[cpu_ops_push_rr]")
{
    regs().sp = 0xCFFF;
    regs().b = 0xAB;
    regs().c = 0xCD;

    runOp(0xC5);
    ASSERT_REGISTERS(0, 0xAB, 0xCD, 0, 0, 0, 0, 0, 0xCFFD, 1);
    REQUIRE(mem(0xCFFE) == 0xAB);
    REQUIRE(mem(0xCFFD) == 0xCD);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xD5", "[cpu_ops_push_rr]")
{
    regs().sp = 0xCFFF;
    regs().d = 0xAB;
    regs().e = 0xCD;

    runOp(0xD5);
    ASSERT_REGISTERS(0, 0, 0, 0xAB, 0xCD, 0, 0, 0, 0xCFFD, 1);
    REQUIRE(mem(0xCFFE) == 0xAB);
    REQUIRE(mem(0xCFFD) == 0xCD);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xE5", "[cpu_ops_push_rr]")
{
    regs().sp = 0xCFFF;
    regs().h = 0xAB;
    regs().l = 0xCD;

    runOp(0xE5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0xCFFD, 1);
    REQUIRE(mem(0xCFFE) == 0xAB);
    REQUIRE(mem(0xCFFD) == 0xCD);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xF5", "[cpu_ops_push_rr]")
{
    regs().sp = 0xCFFF;
    regs().a = 0xAB;
    regs().f = 0xCD;

    runOp(0xF5);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0xCD, 0, 0, 0xCFFD, 1);
    REQUIRE(mem(0xCFFE) == 0xAB);
    REQUIRE(mem(0xCFFD) == 0xCD);
    REQUIRE(ticks() == 16);
}