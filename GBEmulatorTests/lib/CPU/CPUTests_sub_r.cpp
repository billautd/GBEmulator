#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x90", "[cpu_ops_sub_r]")
{
    regs().a = 0xAB;
    regs().b = 0x01;
    runOp(0x90);
    ASSERT_REGISTERS(0xAA, 0x01, 0, 0, 0, 0b01000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().b = 0x0F;
    runOp(0x90);
    ASSERT_REGISTERS(0x9C, 0x0F, 0, 0, 0, 0b01100000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xAB;
    regs().b = 0xCC;
    runOp(0x90);
    ASSERT_REGISTERS(0xDF, 0xCC, 0, 0, 0, 0b01110000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xAB;
    regs().b = 0xAB;
    runOp(0x90);
    ASSERT_REGISTERS(0, 0xAB, 0, 0, 0, 0b11000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x91", "[cpu_ops_sub_r]")
{
    regs().a = 0xAB;
    regs().c = 0x01;
    runOp(0x91);
    ASSERT_REGISTERS(0xAA, 0, 0x01, 0, 0, 0b01000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().c = 0x0F;
    runOp(0x91);
    ASSERT_REGISTERS(0x9C, 0, 0x0F, 0, 0, 0b01100000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xAB;
    regs().c = 0xCC;
    runOp(0x91);
    ASSERT_REGISTERS(0xDF, 0, 0xCC, 0, 0, 0b01110000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xAB;
    regs().c = 0xAB;
    runOp(0x91);
    ASSERT_REGISTERS(0, 0, 0xAB, 0, 0, 0b11000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x92", "[cpu_ops_sub_r]")
{
    regs().a = 0xAB;
    regs().d = 0x01;
    runOp(0x92);
    ASSERT_REGISTERS(0xAA, 0, 0, 0x01, 0, 0b01000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().d = 0x0F;
    runOp(0x92);
    ASSERT_REGISTERS(0x9C, 0, 0, 0x0F, 0, 0b01100000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xAB;
    regs().d = 0xCC;
    runOp(0x92);
    ASSERT_REGISTERS(0xDF, 0, 0, 0xCC, 0, 0b01110000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xAB;
    regs().d = 0xAB;
    runOp(0x92);
    ASSERT_REGISTERS(0, 0, 0, 0xAB, 0, 0b11000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x93", "[cpu_ops_sub_r]")
{
    regs().a = 0xAB;
    regs().e = 0x01;
    runOp(0x93);
    ASSERT_REGISTERS(0xAA, 0, 0, 0, 0x01, 0b01000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().e = 0x0F;
    runOp(0x93);
    ASSERT_REGISTERS(0x9C, 0, 0, 0, 0x0F, 0b01100000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xAB;
    regs().e = 0xCC;
    runOp(0x93);
    ASSERT_REGISTERS(0xDF, 0, 0, 0, 0xCC, 0b01110000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xAB;
    regs().e = 0xAB;
    runOp(0x93);
    ASSERT_REGISTERS(0, 0, 0, 0, 0xAB, 0b11000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x94", "[cpu_ops_sub_r]")
{
    regs().a = 0xAB;
    regs().h = 0x01;
    runOp(0x94);
    ASSERT_REGISTERS(0xAA, 0, 0, 0, 0, 0b01000000, 0x01, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().h = 0x0F;
    runOp(0x94);
    ASSERT_REGISTERS(0x9C, 0, 0, 0, 0, 0b01100000, 0x0F, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xAB;
    regs().h = 0xCC;
    runOp(0x94);
    ASSERT_REGISTERS(0xDF, 0, 0, 0, 0, 0b01110000, 0xCC, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xAB;
    regs().h = 0xAB;
    runOp(0x94);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b11000000, 0xAB, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x95", "[cpu_ops_sub_r]")
{
    regs().a = 0xAB;
    regs().l = 0x01;
    runOp(0x95);
    ASSERT_REGISTERS(0xAA, 0, 0, 0, 0, 0b01000000, 0, 0x01, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().l = 0x0F;
    runOp(0x95);
    ASSERT_REGISTERS(0x9C, 0, 0, 0, 0, 0b01100000, 0, 0x0F, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xAB;
    regs().l = 0xCC;
    runOp(0x95);
    ASSERT_REGISTERS(0xDF, 0, 0, 0, 0, 0b01110000, 0, 0xCC, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xAB;
    regs().l = 0xAB;
    runOp(0x95);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b11000000, 0, 0xAB, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x97", "[cpu_ops_sub_r]")
{
    regs().a = 0xAB;
    runOp(0x97);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b11000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);
}