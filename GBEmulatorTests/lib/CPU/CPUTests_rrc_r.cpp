#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB08", "[cpu_ops_rrc_r]")
{
    regs().b = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x08);
    ASSERT_REGISTERS(0, 0b11100001, 0, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x08);
    ASSERT_REGISTERS(0, 0b00100001, 0, 0, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().b = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x08);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB09", "[cpu_ops_rrc_r]")
{
    regs().c = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x09);
    ASSERT_REGISTERS(0, 0, 0b11100001, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x09);
    ASSERT_REGISTERS(0, 0, 0b00100001, 0, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().c = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x09);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB0A", "[cpu_ops_rrc_r]")
{
    regs().d = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x0A);
    ASSERT_REGISTERS(0, 0, 0, 0b11100001, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x0A);
    ASSERT_REGISTERS(0, 0, 0, 0b00100001, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().d = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x0A);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB0B", "[cpu_ops_rrc_r]")
{
    regs().e = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x0B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b11100001, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x0B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b00100001, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().e = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x0B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB0C", "[cpu_ops_rrc_r]")
{
    regs().h = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x0C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0b11100001, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x0C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0b00100001, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().h = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x0C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB0D", "[cpu_ops_rrc_r]")
{
    regs().l = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x0D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0b11100001, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x0D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0b00100001, 0, 4);
    REQUIRE(ticks() == 16);

    regs().l = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x0D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB0F", "[cpu_ops_rrc_r]")
{
    regs().a = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x0F);
    ASSERT_REGISTERS(0b11100001, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x0F);
    ASSERT_REGISTERS(0b00100001, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().a = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x0F);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}