#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x70", "[cpu_ops_ld_hl_r]")
{
    regs().b = 0x01;
    regs().h = 0x12;
    regs().l = 0x34;

    runOp(0x70);
    ASSERT_REGISTERS(0, 0x01, 0, 0, 0, 0, 0x12, 0x34, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x01);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x71", "[cpu_ops_ld_hl_r]")
{
    regs().c = 0x01;
    regs().h = 0x12;
    regs().l = 0x34;

    runOp(0x71);
    ASSERT_REGISTERS(0, 0, 0x01, 0, 0, 0, 0x12, 0x34, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x01);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x72", "[cpu_ops_ld_hl_r]")
{
    regs().d = 0x01;
    regs().h = 0x12;
    regs().l = 0x34;

    runOp(0x72);
    ASSERT_REGISTERS(0, 0, 0, 0x01, 0, 0, 0x12, 0x34, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x01);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x73", "[cpu_ops_ld_hl_r]")
{
    regs().e = 0x01;
    regs().h = 0x12;
    regs().l = 0x34;

    runOp(0x73);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x01, 0, 0x12, 0x34, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x01);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x74", "[cpu_ops_ld_hl_r]")
{
    regs().h = 0x12;
    regs().l = 0x34;

    runOp(0x74);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0x12, 0x34, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x12);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x75", "[cpu_ops_ld_hl_r]")
{
    regs().h = 0x12;
    regs().l = 0x34;

    runOp(0x75);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0x12, 0x34, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x34);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x77", "[cpu_ops_ld_hl_r]")
{
    regs().a = 0x01;
    regs().h = 0x12;
    regs().l = 0x34;

    runOp(0x77);
    ASSERT_REGISTERS(0x01, 0, 0, 0, 0, 0, 0x12, 0x34, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x01);
    REQUIRE(ticks() == 8);
}