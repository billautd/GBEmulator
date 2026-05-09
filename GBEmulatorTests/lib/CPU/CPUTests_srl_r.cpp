#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB38", "[cpu_ops_srl_r]")
{
    regs().b = 0b11000011;
    runCBPrefixOp(0x38);
    ASSERT_REGISTERS(0, 0b01100001, 0, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0;
    runCBPrefixOp(0x38);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().b = 0b01110000;
    runCBPrefixOp(0x38);
    ASSERT_REGISTERS(0, 0b00111000, 0, 0, 0, 0b00000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB39", "[cpu_ops_srl_r]")
{
    regs().c = 0b11000011;
    runCBPrefixOp(0x39);
    ASSERT_REGISTERS(0, 0, 0b01100001, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0;
    runCBPrefixOp(0x39);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().c = 0b01110000;
    runCBPrefixOp(0x39);
    ASSERT_REGISTERS(0, 0, 0b00111000, 0, 0, 0b00000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB3A", "[cpu_ops_srl_r]")
{
    regs().d = 0b11000011;
    runCBPrefixOp(0x3A);
    ASSERT_REGISTERS(0, 0, 0, 0b01100001, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0;
    runCBPrefixOp(0x3A);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().d = 0b01110000;
    runCBPrefixOp(0x3A);
    ASSERT_REGISTERS(0, 0, 0, 0b00111000, 0, 0b00000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB3B", "[cpu_ops_srl_r]")
{
    regs().e = 0b11000011;
    runCBPrefixOp(0x3B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01100001, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0;
    runCBPrefixOp(0x3B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().e = 0b01110000;
    runCBPrefixOp(0x3B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b00111000, 0b00000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB3C", "[cpu_ops_srl_r]")
{
    regs().h = 0b11000011;
    runCBPrefixOp(0x3C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0b01100001, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0;
    runCBPrefixOp(0x3C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().h = 0b01110000;
    runCBPrefixOp(0x3C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0b00111000, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB3D", "[cpu_ops_srl_r]")
{
    regs().l = 0b11000011;
    runCBPrefixOp(0x3D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0b01100001, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0;
    runCBPrefixOp(0x3D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().l = 0b01110000;
    runCBPrefixOp(0x3D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0b00111000, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB3F", "[cpu_ops_srl_r]")
{
    regs().a = 0b11000011;
    runCBPrefixOp(0x3F);
    ASSERT_REGISTERS(0b01100001, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0;
    runCBPrefixOp(0x3F);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().a = 0b01110000;
    runCBPrefixOp(0x3F);
    ASSERT_REGISTERS(0b00111000, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}