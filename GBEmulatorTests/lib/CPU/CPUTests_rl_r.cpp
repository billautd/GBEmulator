#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB10", "[cpu_ops_rl_r]")
{
    regs().b = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x10);
    ASSERT_REGISTERS(0, 0b10000111, 0, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x10);
    ASSERT_REGISTERS(0, 0b10000100, 0, 0, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().b = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x10);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB11", "[cpu_ops_rl_r]")
{
    regs().c = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x11);
    ASSERT_REGISTERS(0, 0, 0b10000111, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x11);
    ASSERT_REGISTERS(0, 0, 0b10000100, 0, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().c = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x11);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB12", "[cpu_ops_rl_r]")
{
    regs().d = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x12);
    ASSERT_REGISTERS(0, 0, 0, 0b10000111, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x12);
    ASSERT_REGISTERS(0, 0, 0, 0b10000100, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().d = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x12);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB13", "[cpu_ops_rl_r]")
{
    regs().e = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x13);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b10000111, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x13);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b10000100, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().e = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x13);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB14", "[cpu_ops_rl_r]")
{
    regs().h = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x14);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0b10000111, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x14);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0b10000100, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().h = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x14);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB15", "[cpu_ops_rl_r]")
{
    regs().l = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x15);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0b10000111, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x15);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0b10000100, 0, 4);
    REQUIRE(ticks() == 16);

    regs().l = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x15);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB17", "[cpu_ops_rl_r]")
{
    regs().a = 0b11000011;
    regs().f = 0b00010000;
    runCBPrefixOp(0x17);
    ASSERT_REGISTERS(0b10000111, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01000010;
    regs().f = 0b00000000;
    runCBPrefixOp(0x17);
    ASSERT_REGISTERS(0b10000100, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().a = 0;
    regs().f = 0b00000000;
    runCBPrefixOp(0x17);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}