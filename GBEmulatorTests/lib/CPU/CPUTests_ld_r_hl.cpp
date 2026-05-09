#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x46", "[cpu_ops_ld_r_hl]")
{
    regs().b = 0x01;
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0x02;
    runOp(0x46);
    ASSERT_REGISTERS(0, 0x02, 0, 0, 0, 0, 0x12, 0x34, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x02);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x4E", "[cpu_ops_ld_r_hl]")
{
    regs().c = 0x01;
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0x02;
    runOp(0x4E);
    ASSERT_REGISTERS(0, 0, 0x02, 0, 0, 0, 0x12, 0x34, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x02);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x56", "[cpu_ops_ld_r_hl]")
{
    regs().d = 0x01;
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0x02;
    runOp(0x56);
    ASSERT_REGISTERS(0, 0, 0, 0x02, 0, 0, 0x12, 0x34, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x02);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x5E", "[cpu_ops_ld_r_hl]")
{
    regs().e = 0x01;
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0x02;
    runOp(0x5E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x02, 0, 0x12, 0x34, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x02);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x66", "[cpu_ops_ld_r_hl]")
{
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0x02;
    runOp(0x66);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0x02, 0x34, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x02);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x6E", "[cpu_ops_ld_r_hl]")
{
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0x02;
    runOp(0x6E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0x12, 0x02, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x02);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x7E", "[cpu_ops_ld_r_hl]")
{
    regs().a = 0x01;
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0x02;
    runOp(0x7E);
    ASSERT_REGISTERS(0x02, 0, 0, 0, 0, 0, 0x12, 0x34, 0, 0x01);
    REQUIRE(mem(0x1234) == 0x02);
    REQUIRE(ticks() == 8);
}