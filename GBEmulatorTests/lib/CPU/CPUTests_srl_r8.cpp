#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB38", "[cpu_ops_srl_r8]")
{
    regs().b = 0b11000011;
    runCBPrefixOp(0x38);
    ASSERT_REGISTERS(0, 0b01100001, 0, 0, 0, 0b00010000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0;
    runCBPrefixOp(0x38);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().b = 0b01110000;
    runCBPrefixOp(0x38);
    ASSERT_REGISTERS(0, 0b00111000, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB39", "[cpu_ops_srl_r8]")
{
    regs().c = 0b11000011;
    runCBPrefixOp(0x39);
    ASSERT_REGISTERS(0, 0, 0b01100001, 0, 0, 0b00010000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0;
    runCBPrefixOp(0x39);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().c = 0b01110000;
    runCBPrefixOp(0x39);
    ASSERT_REGISTERS(0, 0, 0b00111000, 0, 0, 0b00000000, 0, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB3A", "[cpu_ops_srl_r8]")
{
    regs().d = 0b11000011;
    runCBPrefixOp(0x3A);
    ASSERT_REGISTERS(0, 0, 0, 0b01100001, 0, 0b00010000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0;
    runCBPrefixOp(0x3A);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().d = 0b01110000;
    runCBPrefixOp(0x3A);
    ASSERT_REGISTERS(0, 0, 0, 0b00111000, 0, 0b00000000, 0, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB3B", "[cpu_ops_srl_r8]")
{
    regs().e = 0b11000011;
    runCBPrefixOp(0x3B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01100001, 0b00010000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0;
    runCBPrefixOp(0x3B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().e = 0b01110000;
    runCBPrefixOp(0x3B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b00111000, 0b00000000, 0, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB3C", "[cpu_ops_srl_r8]")
{
    regs().h = 0b11000011;
    runCBPrefixOp(0x3C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0b01100001, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0;
    runCBPrefixOp(0x3C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().h = 0b01110000;
    runCBPrefixOp(0x3C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0b00111000, 0, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB3D", "[cpu_ops_srl_r8]")
{
    regs().l = 0b11000011;
    runCBPrefixOp(0x3D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0, 0b01100001, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0;
    runCBPrefixOp(0x3D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().l = 0b01110000;
    runCBPrefixOp(0x3D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0b00111000, 0, 6);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB3E", "[cpu_ops_srl_r8]")
{
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0b11000011;
    runCBPrefixOp(0x3E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0x12, 0x34, 0, 2);
    REQUIRE(mem(0x1234) == 0b01100001);
    REQUIRE(ticks() == 16);

    mem(0x1234) = 0;
    runCBPrefixOp(0x3E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0x12, 0x34, 0, 4);
    REQUIRE(mem(0x1234) == 0);
    REQUIRE(ticks() == 32);

    mem(0x1234) = 0b01110000;
    runCBPrefixOp(0x3E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0x12, 0x34, 0, 6);
    REQUIRE(mem(0x1234) == 0b00111000);
    REQUIRE(ticks() == 48);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB3F", "[cpu_ops_srl_r8]")
{
    regs().a = 0b11000011;
    runCBPrefixOp(0x3F);
    ASSERT_REGISTERS(0b01100001, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0;
    runCBPrefixOp(0x3F);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().a = 0b01110000;
    runCBPrefixOp(0x3F);
    ASSERT_REGISTERS(0b00111000, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0, 6);
    REQUIRE(ticks() == 24);
}