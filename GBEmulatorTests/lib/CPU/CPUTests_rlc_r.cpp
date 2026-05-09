#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB00", "[cpu_ops_rlc_r]")
{
    regs().b = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x00);
    ASSERT_REGISTERS(0, 0b10000111, 0, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x00);
    ASSERT_REGISTERS(0, 0b10000100, 0, 0, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().b = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x00);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB01", "[cpu_ops_rlc_r]")
{
    regs().c = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x01);
    ASSERT_REGISTERS(0, 0, 0b10000111, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x01);
    ASSERT_REGISTERS(0, 0, 0b10000100, 0, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().c = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x01);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB02", "[cpu_ops_rlc_r]")
{
    regs().d = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x02);
    ASSERT_REGISTERS(0, 0, 0, 0b10000111, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x02);
    ASSERT_REGISTERS(0, 0, 0, 0b10000100, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().d = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x02);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB03", "[cpu_ops_rlc_r]")
{
    regs().e = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x03);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b10000111, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x03);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b10000100, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().e = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x03);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB04", "[cpu_ops_rlc_r]")
{
    regs().h = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x04);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0b10000111, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x04);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0b10000100, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().h = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x04);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB05", "[cpu_ops_rlc_r]")
{
    regs().l = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x05);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0b10000111, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x05);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0b10000100, 0, 4);
    REQUIRE(ticks() == 16);

    regs().l = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x05);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB07", "[cpu_ops_rlc_r]")
{
    regs().a = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x07);
    ASSERT_REGISTERS(0b10000111, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x07);
    ASSERT_REGISTERS(0b10000100, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().a = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x07);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}