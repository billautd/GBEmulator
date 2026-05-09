#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x40", "[cpu_ops_ld_r1_r2]")
{
    regs().b = 0x01;
    regs().b = 0x02;
    runOp(0x40);
    ASSERT_REGISTERS(0, 0x02, 0, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x41", "[cpu_ops_ld_r1_r2]")
{
    regs().b = 0x01;
    regs().c = 0x02;
    runOp(0x41);
    ASSERT_REGISTERS(0, 0x02, 0x02, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x42", "[cpu_ops_ld_r1_r2]")
{
    regs().b = 0x01;
    regs().d = 0x02;
    runOp(0x42);
    ASSERT_REGISTERS(0, 0x02, 0, 0x02, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x43", "[cpu_ops_ld_r1_r2]")
{
    regs().b = 0x01;
    regs().e = 0x02;
    runOp(0x43);
    ASSERT_REGISTERS(0, 0x02, 0, 0, 0x02, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x44", "[cpu_ops_ld_r1_r2]")
{
    regs().b = 0x01;
    regs().h = 0x02;
    runOp(0x44);
    ASSERT_REGISTERS(0, 0x02, 0, 0, 0, 0, 0x02, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x45", "[cpu_ops_ld_r1_r2]")
{
    regs().b = 0x01;
    regs().l = 0x02;
    runOp(0x45);
    ASSERT_REGISTERS(0, 0x02, 0, 0, 0, 0, 0, 0x02, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x47", "[cpu_ops_ld_r1_r2]")
{
    regs().b = 0x01;
    regs().a = 0x02;
    runOp(0x47);
    ASSERT_REGISTERS(0x02, 0x02, 0, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x48", "[cpu_ops_ld_r1_r2]")
{
    regs().c = 0x01;
    regs().b = 0x02;
    runOp(0x48);
    ASSERT_REGISTERS(0, 0x02, 0x02, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x49", "[cpu_ops_ld_r1_r2]")
{
    regs().c = 0x01;
    regs().c = 0x02;
    runOp(0x49);
    ASSERT_REGISTERS(0, 0, 0x02, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x4A", "[cpu_ops_ld_r1_r2]")
{
    regs().c = 0x01;
    regs().d = 0x02;
    runOp(0x4A);
    ASSERT_REGISTERS(0, 0, 0x02, 0x02, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x4B", "[cpu_ops_ld_r1_r2]")
{
    regs().c = 0x01;
    regs().e = 0x02;
    runOp(0x4B);
    ASSERT_REGISTERS(0, 0, 0x02, 0, 0x02, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x4C", "[cpu_ops_ld_r1_r2]")
{
    regs().c = 0x01;
    regs().h = 0x02;
    runOp(0x4C);
    ASSERT_REGISTERS(0, 0, 0x02, 0, 0, 0, 0x02, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x4D", "[cpu_ops_ld_r1_r2]")
{
    regs().c = 0x01;
    regs().l = 0x02;
    runOp(0x4D);
    ASSERT_REGISTERS(0, 0, 0x02, 0, 0, 0, 0, 0x02, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x4F", "[cpu_ops_ld_r1_r2]")
{
    regs().c = 0x01;
    regs().a = 0x02;
    runOp(0x4F);
    ASSERT_REGISTERS(0x02, 0, 0x02, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x50", "[cpu_ops_ld_r1_r2]")
{
    regs().d = 0x01;
    regs().b = 0x02;
    runOp(0x50);
    ASSERT_REGISTERS(0, 0x02, 0, 0x02, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x51", "[cpu_ops_ld_r1_r2]")
{
    regs().d = 0x01;
    regs().c = 0x02;
    runOp(0x51);
    ASSERT_REGISTERS(0, 0, 0x02, 0x02, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x52", "[cpu_ops_ld_r1_r2]")
{
    regs().d = 0x01;
    regs().d = 0x02;
    runOp(0x52);
    ASSERT_REGISTERS(0, 0, 0, 0x02, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x53", "[cpu_ops_ld_r1_r2]")
{
    regs().d = 0x01;
    regs().e = 0x02;
    runOp(0x53);
    ASSERT_REGISTERS(0, 0, 0, 0x02, 0x02, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x54", "[cpu_ops_ld_r1_r2]")
{
    regs().d = 0x01;
    regs().h = 0x02;
    runOp(0x54);
    ASSERT_REGISTERS(0, 0, 0, 0x02, 0, 0, 0x02, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x55", "[cpu_ops_ld_r1_r2]")
{
    regs().d = 0x01;
    regs().l = 0x02;
    runOp(0x55);
    ASSERT_REGISTERS(0, 0, 0, 0x02, 0, 0, 0, 0x02, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x57", "[cpu_ops_ld_r1_r2]")
{
    regs().d = 0x01;
    regs().a = 0x02;
    runOp(0x57);
    ASSERT_REGISTERS(0x02, 0, 0, 0x02, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x58", "[cpu_ops_ld_r1_r2]")
{
    regs().e = 0x01;
    regs().b = 0x02;
    runOp(0x58);
    ASSERT_REGISTERS(0, 0x02, 0, 0, 0x02, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x59", "[cpu_ops_ld_r1_r2]")
{
    regs().e = 0x01;
    regs().c = 0x02;
    runOp(0x59);
    ASSERT_REGISTERS(0, 0, 0x02, 0, 0x02, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x5A", "[cpu_ops_ld_r1_r2]")
{
    regs().e = 0x01;
    regs().d = 0x02;
    runOp(0x5A);
    ASSERT_REGISTERS(0, 0, 0, 0x02, 0x02, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x5B", "[cpu_ops_ld_r1_r2]")
{
    regs().e = 0x01;
    regs().e = 0x02;
    runOp(0x5B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x02, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x5C", "[cpu_ops_ld_r1_r2]")
{
    regs().e = 0x01;
    regs().h = 0x02;
    runOp(0x5C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x02, 0, 0x02, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x5D", "[cpu_ops_ld_r1_r2]")
{
    regs().e = 0x01;
    regs().l = 0x02;
    runOp(0x5D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x02, 0, 0, 0x02, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x5F", "[cpu_ops_ld_r1_r2]")
{
    regs().e = 0x01;
    regs().a = 0x02;
    runOp(0x5F);
    ASSERT_REGISTERS(0x02, 0, 0, 0, 0x02, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x60", "[cpu_ops_ld_r1_r2]")
{
    regs().h = 0x01;
    regs().b = 0x02;
    runOp(0x60);
    ASSERT_REGISTERS(0, 0x02, 0, 0, 0, 0, 0x02, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x61", "[cpu_ops_ld_r1_r2]")
{
    regs().h = 0x01;
    regs().c = 0x02;
    runOp(0x61);
    ASSERT_REGISTERS(0, 0, 0x02, 0, 0, 0, 0x02, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x62", "[cpu_ops_ld_r1_r2]")
{
    regs().h = 0x01;
    regs().d = 0x02;
    runOp(0x62);
    ASSERT_REGISTERS(0, 0, 0, 0x02, 0, 0, 0x02, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x63", "[cpu_ops_ld_r1_r2]")
{
    regs().h = 0x01;
    regs().e = 0x02;
    runOp(0x63);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x02, 0, 0x02, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x64", "[cpu_ops_ld_r1_r2]")
{
    regs().h = 0x01;
    regs().h = 0x02;
    runOp(0x64);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0x02, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x65", "[cpu_ops_ld_r1_r2]")
{
    regs().h = 0x01;
    regs().l = 0x02;
    runOp(0x65);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0x02, 0x02, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x67", "[cpu_ops_ld_r1_r2]")
{
    regs().h = 0x01;
    regs().a = 0x02;
    runOp(0x67);
    ASSERT_REGISTERS(0x02, 0, 0, 0, 0, 0, 0x02, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x68", "[cpu_ops_ld_r1_r2]")
{
    regs().l = 0x01;
    regs().b = 0x02;
    runOp(0x68);
    ASSERT_REGISTERS(0, 0x02, 0, 0, 0, 0, 0, 0x02, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x69", "[cpu_ops_ld_r1_r2]")
{
    regs().l = 0x01;
    regs().c = 0x02;
    runOp(0x69);
    ASSERT_REGISTERS(0, 0, 0x02, 0, 0, 0, 0, 0x02, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x6A", "[cpu_ops_ld_r1_r2]")
{
    regs().l = 0x01;
    regs().d = 0x02;
    runOp(0x6A);
    ASSERT_REGISTERS(0, 0, 0, 0x02, 0, 0, 0, 0x02, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x6B", "[cpu_ops_ld_r1_r2]")
{
    regs().l = 0x01;
    regs().e = 0x02;
    runOp(0x6B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x02, 0, 0, 0x02, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x6C", "[cpu_ops_ld_r1_r2]")
{
    regs().l = 0x01;
    regs().h = 0x02;
    runOp(0x6C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0x02, 0x02, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x6D", "[cpu_ops_ld_r1_r2]")
{
    regs().l = 0x01;
    regs().l = 0x02;
    runOp(0x6D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0x02, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x6F", "[cpu_ops_ld_r1_r2]")
{
    regs().l = 0x01;
    regs().a = 0x02;
    runOp(0x6F);
    ASSERT_REGISTERS(0x02, 0, 0, 0, 0, 0, 0, 0x02, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x78", "[cpu_ops_ld_r1_r2]")
{
    regs().a = 0x01;
    regs().b = 0x02;
    runOp(0x78);
    ASSERT_REGISTERS(0x02, 0x02, 0, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x79", "[cpu_ops_ld_r1_r2]")
{
    regs().a = 0x01;
    regs().c = 0x02;
    runOp(0x79);
    ASSERT_REGISTERS(0x02, 0, 0x02, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x7A", "[cpu_ops_ld_r1_r2]")
{
    regs().a = 0x01;
    regs().d = 0x02;
    runOp(0x7A);
    ASSERT_REGISTERS(0x02, 0, 0, 0x02, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x7B", "[cpu_ops_ld_r1_r2]")
{
    regs().a = 0x01;
    regs().e = 0x02;
    runOp(0x7B);
    ASSERT_REGISTERS(0x02, 0, 0, 0, 0x02, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x7C", "[cpu_ops_ld_r1_r2]")
{
    regs().a = 0x01;
    regs().h = 0x02;
    runOp(0x7C);
    ASSERT_REGISTERS(0x02, 0, 0, 0, 0, 0, 0x02, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x7D", "[cpu_ops_ld_r1_r2]")
{
    regs().a = 0x01;
    regs().l = 0x02;
    runOp(0x7D);
    ASSERT_REGISTERS(0x02, 0, 0, 0, 0, 0, 0, 0x02, 0, 0x01);
    REQUIRE(ticks() == 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x7F", "[cpu_ops_ld_r1_r2]")
{
    regs().a = 0x01;
    regs().a = 0x02;
    runOp(0x7F);
    ASSERT_REGISTERS(0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x01);
    REQUIRE(ticks() == 4);
}