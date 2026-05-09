#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x09", "[cpu_ops_add_hl_rr]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    regs().b = 0x01;
    regs().c = 0x02;

    runOp(0x09);

    ASSERT_REGISTERS(0, 0x01, 0x02, 0, 0, 0, 0xAC, 0xCF, 0, 1);
    REQUIRE(ticks() == 8);

    regs().h = 0x0F;
    regs().l = 0xFF;
    regs().b = 0x00;
    regs().c = 0x01;

    runOp(0x09);

    ASSERT_REGISTERS(0, 0, 0x01, 0, 0, 0b00100000, 0x10, 0, 0, 2);
    REQUIRE(ticks() == 16);

    regs().h = 0xFF;
    regs().l = 0xFF;
    regs().b = 0xFF;
    regs().c = 0xFF;

    runOp(0x09);

    ASSERT_REGISTERS(0, 0xFF, 0xFF, 0, 0, 0b00110000, 0xFF, 0xFE, 0, 3);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x19", "[cpu_ops_add_hl_rr]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    regs().d = 0x01;
    regs().e = 0x02;

    runOp(0x19);

    ASSERT_REGISTERS(0, 0, 0, 0x01, 0x02, 0, 0xAC, 0xCF, 0, 1);
    REQUIRE(ticks() == 8);

    regs().h = 0x0F;
    regs().l = 0xFF;
    regs().d = 0x00;
    regs().e = 0x01;

    runOp(0x19);

    ASSERT_REGISTERS(0, 0, 0, 0, 0x01, 0b00100000, 0x10, 0, 0, 2);
    REQUIRE(ticks() == 16);

    regs().h = 0xFF;
    regs().l = 0xFF;
    regs().d = 0xFF;
    regs().e = 0xFF;

    runOp(0x19);

    ASSERT_REGISTERS(0, 0, 0, 0xFF, 0xFF, 0b00110000, 0xFF, 0xFE, 0, 3);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x29", "[cpu_ops_add_hl_rr]")
{
    regs().h = 0x01;
    regs().l = 0x01;

    runOp(0x29);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0x02, 0x02, 0, 1);
    REQUIRE(ticks() == 8);

    regs().h = 0x0F;
    regs().l = 0xFF;

    runOp(0x29);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0x1F, 0xFE, 0, 2);
    REQUIRE(ticks() == 16);

    regs().h = 0xFF;
    regs().l = 0xFF;

    runOp(0x29);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00110000, 0xFF, 0xFE, 0, 3);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x39", "[cpu_ops_add_hl_rr]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    regs().sp = 0x0102;

    runOp(0x39);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAC, 0xCF, 0x0102, 1);
    REQUIRE(ticks() == 8);

    regs().h = 0x0F;
    regs().l = 0xFF;
    regs().sp = 0x0001;

    runOp(0x39);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0x10, 0, 0x0001, 2);
    REQUIRE(ticks() == 16);

    regs().h = 0xFF;
    regs().l = 0xFF;
    regs().sp = 0xFFFF;

    runOp(0x39);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00110000, 0xFF, 0xFE, 0xFFFF, 3);
    REQUIRE(ticks() == 24);
}