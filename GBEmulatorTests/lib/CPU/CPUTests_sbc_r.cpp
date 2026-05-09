#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x98", "[cpu_ops_sbc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().b = 0x01;
    runOp(0x98);
    ASSERT_REGISTERS(0xA9, 0x01, 0, 0, 0, 0b01000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().b = 0x0F;
    runOp(0x98);
    ASSERT_REGISTERS(0x9B, 0x0F, 0, 0, 0, 0b01100000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    regs().b = 0xCC;
    runOp(0x98);
    ASSERT_REGISTERS(0xDF, 0xCC, 0, 0, 0, 0b01110000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xAB;
    regs().b = 0xAB;
    regs().f = 0b00000000;
    runOp(0x98);
    ASSERT_REGISTERS(0, 0xAB, 0, 0, 0, 0b11000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x99", "[cpu_ops_sbc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().c = 0x01;
    runOp(0x99);
    ASSERT_REGISTERS(0xA9, 0, 0x01, 0, 0, 0b01000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().c = 0x0F;
    runOp(0x99);
    ASSERT_REGISTERS(0x9B, 0, 0x0F, 0, 0, 0b01100000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    regs().c = 0xCC;
    runOp(0x99);
    ASSERT_REGISTERS(0xDF, 0, 0xCC, 0, 0, 0b01110000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    regs().c = 0xAB;
    runOp(0x99);
    ASSERT_REGISTERS(0, 0, 0xAB, 0, 0, 0b11000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x9A", "[cpu_ops_sbc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().d = 0x01;
    runOp(0x9A);
    ASSERT_REGISTERS(0xA9, 0, 0, 0x01, 0, 0b01000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().d = 0x0F;
    runOp(0x9A);
    ASSERT_REGISTERS(0x9B, 0, 0, 0x0F, 0, 0b01100000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    regs().d = 0xCC;
    runOp(0x9A);
    ASSERT_REGISTERS(0xDF, 0, 0, 0xCC, 0, 0b01110000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    regs().d = 0xAB;
    runOp(0x9A);
    ASSERT_REGISTERS(0, 0, 0, 0xAB, 0, 0b11000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x9B", "[cpu_ops_sbc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().e = 0x01;
    runOp(0x9B);
    ASSERT_REGISTERS(0xA9, 0, 0, 0, 0x01, 0b01000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().e = 0x0F;
    runOp(0x9B);
    ASSERT_REGISTERS(0x9B, 0, 0, 0, 0x0F, 0b01100000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    regs().e = 0xCC;
    runOp(0x9B);
    ASSERT_REGISTERS(0xDF, 0, 0, 0, 0xCC, 0b01110000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    regs().e = 0xAB;
    runOp(0x9B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0xAB, 0b11000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x9C", "[cpu_ops_sbc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().h = 0x01;
    runOp(0x9C);
    ASSERT_REGISTERS(0xA9, 0, 0, 0, 0, 0b01000000, 0x01, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().h = 0x0F;
    runOp(0x9C);
    ASSERT_REGISTERS(0x9B, 0, 0, 0, 0, 0b01100000, 0x0F, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    regs().h = 0xCC;
    runOp(0x9C);
    ASSERT_REGISTERS(0xDF, 0, 0, 0, 0, 0b01110000, 0xCC, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    regs().h = 0xAB;
    runOp(0x9C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b11000000, 0xAB, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x9D", "[cpu_ops_sbc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().l = 0x01;
    runOp(0x9D);
    ASSERT_REGISTERS(0xA9, 0, 0, 0, 0, 0b01000000, 0, 0x01, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().l = 0x0F;
    runOp(0x9D);
    ASSERT_REGISTERS(0x9B, 0, 0, 0, 0, 0b01100000, 0, 0x0F, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    regs().l = 0xCC;
    runOp(0x9D);
    ASSERT_REGISTERS(0xDF, 0, 0, 0, 0, 0b01110000, 0, 0xCC, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    regs().l = 0xAB;
    runOp(0x9D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b11000000, 0, 0xAB, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x9F", "[cpu_ops_sbc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    runOp(0x9F);
    ASSERT_REGISTERS(0xFF, 0, 0, 0, 0, 0b01110000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xAB;
    regs().f = 0b00000000;
    runOp(0x9F);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b11000000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}