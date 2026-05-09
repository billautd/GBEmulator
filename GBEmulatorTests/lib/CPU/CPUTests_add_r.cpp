#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x80", "[cpu_ops_add_r]")
{
    regs().a = 0xAB;
    regs().b = 0x10;
    runOp(0x80);
    ASSERT_REGISTERS(0xBB, 0x10, 0, 0, 0, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().b = 0x01;
    runOp(0x80);
    ASSERT_REGISTERS(0, 0x01, 0, 0, 0, 0b10110000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x0F;
    regs().b = 0x01;
    runOp(0x80);
    ASSERT_REGISTERS(0x10, 0x01, 0, 0, 0, 0b00100000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x81", "[cpu_ops_add_r]")
{
    regs().a = 0xAB;
    regs().c = 0x10;
    runOp(0x81);
    ASSERT_REGISTERS(0xBB, 0, 0x10, 0, 0, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().c = 0x01;
    runOp(0x81);
    ASSERT_REGISTERS(0, 0, 0x01, 0, 0, 0b10110000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x0F;
    regs().c = 0x01;
    runOp(0x81);
    ASSERT_REGISTERS(0x10, 0, 0x01, 0, 0, 0b00100000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x82", "[cpu_ops_add_r]")
{
    regs().a = 0xAB;
    regs().d = 0x10;
    runOp(0x82);
    ASSERT_REGISTERS(0xBB, 0, 0, 0x10, 0, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().d = 0x01;
    runOp(0x82);
    ASSERT_REGISTERS(0, 0, 0, 0x01, 0, 0b10110000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x0F;
    regs().d = 0x01;
    runOp(0x82);
    ASSERT_REGISTERS(0x10, 0, 0, 0x01, 0, 0b00100000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x83", "[cpu_ops_add_r]")
{
    regs().a = 0xAB;
    regs().e = 0x10;
    runOp(0x83);
    ASSERT_REGISTERS(0xBB, 0, 0, 0, 0x10, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().e = 0x01;
    runOp(0x83);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x01, 0b10110000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x0F;
    regs().e = 0x01;
    runOp(0x83);
    ASSERT_REGISTERS(0x10, 0, 0, 0, 0x01, 0b00100000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x84", "[cpu_ops_add_r]")
{
    regs().a = 0xAB;
    regs().h = 0x10;
    runOp(0x84);
    ASSERT_REGISTERS(0xBB, 0, 0, 0, 0, 0b00000000, 0x10, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().h = 0x01;
    runOp(0x84);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10110000, 0x01, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x0F;
    regs().h = 0x01;
    runOp(0x84);
    ASSERT_REGISTERS(0x10, 0, 0, 0, 0, 0b00100000, 0x01, 0, 0, 3);
    REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x85", "[cpu_ops_add_r]")
{
    regs().a = 0xAB;
    regs().l = 0x10;
    runOp(0x85);
    ASSERT_REGISTERS(0xBB, 0, 0, 0, 0, 0b00000000, 0, 0x10, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFF;
    regs().l = 0x01;
    runOp(0x85);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10110000, 0, 0x01, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x0F;
    regs().l = 0x01;
    runOp(0x85);
    ASSERT_REGISTERS(0x10, 0, 0, 0, 0, 0b00100000, 0, 0x01, 0, 3);
    REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x87", "[cpu_ops_add_r]")
{
    regs().a = 0x01;
    runOp(0x87);
    ASSERT_REGISTERS(0x02, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0;
    runOp(0x87);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xFF;
    runOp(0x87);
    ASSERT_REGISTERS(0xFE, 0, 0, 0, 0, 0b00110000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0x1F;
    runOp(0x87);
    ASSERT_REGISTERS(0x3E, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}