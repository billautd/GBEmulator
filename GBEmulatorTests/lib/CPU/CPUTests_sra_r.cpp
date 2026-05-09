#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB28", "[cpu_ops_sra_r]")
{
    regs().b = 0b11000011;
    runCBPrefixOp(0x28);
    ASSERT_REGISTERS(0, 0b11100001, 0, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0;
    runCBPrefixOp(0x28);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().b = 0b01110000;
    runCBPrefixOp(0x28);
    ASSERT_REGISTERS(0, 0b00111000, 0, 0, 0, 0b00000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB29", "[cpu_ops_sra_r]")
{
    regs().c = 0b11000011;
    runCBPrefixOp(0x29);
    ASSERT_REGISTERS(0, 0, 0b11100001, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0;
    runCBPrefixOp(0x29);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().c = 0b01110000;
    runCBPrefixOp(0x29);
    ASSERT_REGISTERS(0, 0, 0b00111000, 0, 0, 0b00000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB2A", "[cpu_ops_sra_r]")
{
    regs().d = 0b11000011;
    runCBPrefixOp(0x2A);
    ASSERT_REGISTERS(0, 0, 0, 0b11100001, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0;
    runCBPrefixOp(0x2A);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().d = 0b01110000;
    runCBPrefixOp(0x2A);
    ASSERT_REGISTERS(0, 0, 0, 0b00111000, 0, 0b00000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB2B", "[cpu_ops_sra_r]")
{
    regs().e = 0b11000011;
    runCBPrefixOp(0x2B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b11100001, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0;
    runCBPrefixOp(0x2B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().e = 0b01110000;
    runCBPrefixOp(0x2B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b00111000, 0b00000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB2C", "[cpu_ops_sra_r]")
{
    regs().h = 0b11000011;
    runCBPrefixOp(0x2C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0b11100001, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0;
    runCBPrefixOp(0x2C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().h = 0b01110000;
    runCBPrefixOp(0x2C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0b00111000, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB2D", "[cpu_ops_sra_r]")
{
    regs().l = 0b11000011;
    runCBPrefixOp(0x2D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0b11100001, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0;
    runCBPrefixOp(0x2D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().l = 0b01110000;
    runCBPrefixOp(0x2D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0b00111000, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB2F", "[cpu_ops_sra_r]")
{
    regs().a = 0b11000011;
    runCBPrefixOp(0x2F);
    ASSERT_REGISTERS(0b11100001, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0;
    runCBPrefixOp(0x2F);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().a = 0b01110000;
    runCBPrefixOp(0x2F);
    ASSERT_REGISTERS(0b00111000, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}