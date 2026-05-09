#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x03", "[cpu_ops_inc_rr]")
{
    regs().b = 0x00;
    regs().c = 0x01;
    runOp(0x03);
    ASSERT_REGISTERS(0, 0, 0x02, 0, 0, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 8);

    regs().b = 0x00;
    regs().c = 0xFF;
    runOp(0x03);
    ASSERT_REGISTERS(0, 0x01, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 16);

    regs().b = 0xFF;
    regs().c = 0xFF;
    runOp(0x03);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x13", "[cpu_ops_inc_rr]")
{
    regs().d = 0x00;
    regs().e = 0x01;
    runOp(0x13);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x02, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 8);

    regs().d = 0x00;
    regs().e = 0xFF;
    runOp(0x13);
    ASSERT_REGISTERS(0, 0, 0, 0x01, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 16);

    regs().d = 0xFF;
    regs().e = 0xFF;
    runOp(0x13);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x23", "[cpu_ops_inc_rr]")
{
    regs().h = 0x00;
    regs().l = 0x01;
    runOp(0x23);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0x02, 0, 1);
    REQUIRE(ticks() == 8);

    regs().h = 0x00;
    regs().l = 0xFF;
    runOp(0x23);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0x01, 0, 0, 2);
    REQUIRE(ticks() == 16);

    regs().h = 0xFF;
    regs().l = 0xFF;
    runOp(0x23);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x33", "[cpu_ops_inc_rr]")
{
    regs().sp = 0x0001;
    runOp(0x33);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0x0002, 1);
    REQUIRE(ticks() == 8);

    regs().sp = 0x00FF;
    runOp(0x33);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0x0100, 2);
    REQUIRE(ticks() == 16);

    regs().sp = 0xFFFF;
    runOp(0x33);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 24);
}