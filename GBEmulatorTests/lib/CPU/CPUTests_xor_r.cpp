#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xA8", "[cpu_ops_xor_r]")
{
    regs().a = 0xAB;
    regs().b = 0xCD;
    runOp(0xA8);
    ASSERT_REGISTERS(0b01100110, 0xCD, 0, 0, 0, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().b = 0xFF;
    runOp(0xA8);
    ASSERT_REGISTERS(0x00, 0xFF, 0, 0, 0, 0b10000000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xA9", "[cpu_ops_xor_r]")
{
    regs().a = 0xAB;
    regs().c = 0xCD;
    runOp(0xA9);
    ASSERT_REGISTERS(0b01100110, 0, 0xCD, 0, 0, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().c = 0xFF;
    runOp(0xA9);
    ASSERT_REGISTERS(0x00, 0, 0xFF, 0, 0, 0b10000000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xAA", "[cpu_ops_xor_r]")
{
    regs().a = 0xAB;
    regs().d = 0xCD;
    runOp(0xAA);
    ASSERT_REGISTERS(0b01100110, 0, 0, 0xCD, 0, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().d = 0xFF;
    runOp(0xAA);
    ASSERT_REGISTERS(0x00, 0, 0, 0xFF, 0, 0b10000000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xAB", "[cpu_ops_xor_r]")
{
    regs().a = 0xAB;
    regs().e = 0xCD;
    runOp(0xAB);
    ASSERT_REGISTERS(0b01100110, 0, 0, 0, 0xCD, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().e = 0xFF;
    runOp(0xAB);
    ASSERT_REGISTERS(0x00, 0, 0, 0, 0xFF, 0b10000000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xAC", "[cpu_ops_xor_r]")
{
    regs().a = 0xAB;
    regs().h = 0xCD;
    runOp(0xAC);
    ASSERT_REGISTERS(0b01100110, 0, 0, 0, 0, 0b00000000, 0xCD, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().h = 0xFF;
    runOp(0xAC);
    ASSERT_REGISTERS(0x00, 0, 0, 0, 0, 0b10000000, 0xFF, 0, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xAD", "[cpu_ops_xor_r]")
{
    regs().a = 0xAB;
    regs().l = 0xCD;
    runOp(0xAD);
    ASSERT_REGISTERS(0b01100110, 0, 0, 0, 0, 0b00000000, 0, 0xCD, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().l = 0xFF;
    runOp(0xAD);
    ASSERT_REGISTERS(0x00, 0, 0, 0, 0, 0b10000000, 0, 0xFF, 0, 2);
    REQUIRE(ticks() == 8);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xAF", "[cpu_ops_xor_r]")
{
    regs().a = 0xAB;
    runOp(0xAF);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);
}