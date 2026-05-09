#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xB8", "[cpu_ops_cp_r]")
{
    regs().a = 0xAB;
    regs().b = 0xAB;
    runOp(0xB8);
    ASSERT_REGISTERS(0xAB, 0xAB, 0, 0, 0, 0b11000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().b = 0x12;
    runOp(0xB8);
    ASSERT_REGISTERS(0xAB, 0x12, 0, 0, 0, 0b01000000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0x99;
    runOp(0xB8);
    ASSERT_REGISTERS(0xAB, 0x99, 0, 0, 0, 0b01000000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().b = 0xFF;
    runOp(0xB8);
    ASSERT_REGISTERS(0xAB, 0xFF, 0, 0, 0, 0b01110000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xB9", "[cpu_ops_cp_r]")
{
    regs().a = 0xAB;
    regs().c = 0xAB;
    runOp(0xB9);
    ASSERT_REGISTERS(0xAB, 0, 0xAB, 0, 0, 0b11000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().c = 0x12;
    runOp(0xB9);
    ASSERT_REGISTERS(0xAB, 0, 0x12, 0, 0, 0b01000000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0x99;
    runOp(0xB9);
    ASSERT_REGISTERS(0xAB, 0, 0x99, 0, 0, 0b01000000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().c = 0xFF;
    runOp(0xB9);
    ASSERT_REGISTERS(0xAB, 0, 0xFF, 0, 0, 0b01110000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xBA", "[cpu_ops_cp_r]")
{
    regs().a = 0xAB;
    regs().d = 0xAB;
    runOp(0xBA);
    ASSERT_REGISTERS(0xAB, 0, 0, 0xAB, 0, 0b11000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().d = 0x12;
    runOp(0xBA);
    ASSERT_REGISTERS(0xAB, 0, 0, 0x12, 0, 0b01000000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0x99;
    runOp(0xBA);
    ASSERT_REGISTERS(0xAB, 0, 0, 0x99, 0, 0b01000000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().d = 0xFF;
    runOp(0xBA);
    ASSERT_REGISTERS(0xAB, 0, 0, 0xFF, 0, 0b01110000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xBB", "[cpu_ops_cp_r]")
{
    regs().a = 0xAB;
    regs().e = 0xAB;
    runOp(0xBB);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0xAB, 0b11000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().e = 0x12;
    runOp(0xBB);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0x12, 0b01000000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0x99;
    runOp(0xBB);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0x99, 0b01000000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().e = 0xFF;
    runOp(0xBB);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0xFF, 0b01110000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xBC", "[cpu_ops_cp_r]")
{
    regs().a = 0xAB;
    regs().h = 0xAB;
    runOp(0xBC);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b11000000, 0xAB, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().h = 0x12;
    runOp(0xBC);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b01000000, 0x12, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0x99;
    runOp(0xBC);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b01000000, 0x99, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().h = 0xFF;
    runOp(0xBC);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b01110000, 0xFF, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xBD", "[cpu_ops_cp_r]")
{
    regs().a = 0xAB;
    regs().l = 0xAB;
    runOp(0xBD);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b11000000, 0, 0xAB, 0, 1);
    REQUIRE(ticks() == 4);

    regs().l = 0x12;
    runOp(0xBD);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b01000000, 0, 0x12, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0x99;
    runOp(0xBD);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b01000000, 0, 0x99, 0, 3);
    REQUIRE(ticks() == 12);

    regs().l = 0xFF;
    runOp(0xBD);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b01110000, 0, 0xFF, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xBF", "[cpu_ops_cp_r]")
{
    regs().a = 0xAB;
    runOp(0xBF);
    ASSERT_REGISTERS(0xAB, 0, 0, 0, 0, 0b11000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0x12;
    runOp(0xBF);
    ASSERT_REGISTERS(0x12, 0, 0, 0, 0, 0b11000000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x99;
    runOp(0xBF);
    ASSERT_REGISTERS(0x99, 0, 0, 0, 0, 0b11000000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0xFF;
    runOp(0xBF);
    ASSERT_REGISTERS(0xFF, 0, 0, 0, 0, 0b11000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}