#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x88", "[cpu_ops_adc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().b = 0x10;
    runOp(0x88);
    ASSERT_REGISTERS(0xBC, 0x10, 0, 0, 0, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFE;
    regs().f = 0b00010000;
    regs().b = 0x01;
    runOp(0x88);
    ASSERT_REGISTERS(0, 0x01, 0, 0, 0, 0b10110000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x0E;
    regs().f = 0b00010000;
    regs().b = 0x01;
    runOp(0x88);
    ASSERT_REGISTERS(0x10, 0x01, 0, 0, 0, 0b00100000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0x0E;
    regs().f = 0b00000000;
    regs().b = 0x01;
    runOp(0x88);
    ASSERT_REGISTERS(0x0F, 0x01, 0, 0, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x89", "[cpu_ops_adc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().c = 0x10;
    runOp(0x89);
    ASSERT_REGISTERS(0xBC, 0, 0x10, 0, 0, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFE;
    regs().f = 0b00010000;
    regs().c = 0x01;
    runOp(0x89);
    ASSERT_REGISTERS(0, 0, 0x01, 0, 0, 0b10110000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x0E;
    regs().f = 0b00010000;
    regs().c = 0x01;
    runOp(0x89);
    ASSERT_REGISTERS(0x10, 0, 0x01, 0, 0, 0b00100000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0x0E;
    regs().f = 0b00000000;
    regs().c = 0x01;
    runOp(0x89);
    ASSERT_REGISTERS(0x0F, 0, 0x01, 0, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x8A", "[cpu_ops_adc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().d = 0x10;
    runOp(0x8A);
    ASSERT_REGISTERS(0xBC, 0, 0, 0x10, 0, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFE;
    regs().f = 0b00010000;
    regs().d = 0x01;
    runOp(0x8A);
    ASSERT_REGISTERS(0, 0, 0, 0x01, 0, 0b10110000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x0E;
    regs().f = 0b00010000;
    regs().d = 0x01;
    runOp(0x8A);
    ASSERT_REGISTERS(0x10, 0, 0, 0x01, 0, 0b00100000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0x0E;
    regs().f = 0b00000000;
    regs().d = 0x01;
    runOp(0x8A);
    ASSERT_REGISTERS(0x0F, 0, 0, 0x01, 0, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x8B", "[cpu_ops_adc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().e = 0x10;
    runOp(0x8B);
    ASSERT_REGISTERS(0xBC, 0, 0, 0, 0x10, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFE;
    regs().f = 0b00010000;
    regs().e = 0x01;
    runOp(0x8B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x01, 0b10110000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x0E;
    regs().f = 0b00010000;
    regs().e = 0x01;
    runOp(0x8B);
    ASSERT_REGISTERS(0x10, 0, 0, 0, 0x01, 0b00100000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0x0E;
    regs().f = 0b00000000;
    regs().e = 0x01;
    runOp(0x8B);
    ASSERT_REGISTERS(0x0F, 0, 0, 0, 0x01, 0b00000000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x8C", "[cpu_ops_adc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().h = 0x10;
    runOp(0x8C);
    ASSERT_REGISTERS(0xBC, 0, 0, 0, 0, 0b00000000, 0x10, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFE;
    regs().f = 0b00010000;
    regs().h = 0x01;
    runOp(0x8C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10110000, 0x01, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x0E;
    regs().f = 0b00010000;
    regs().h = 0x01;
    runOp(0x8C);
    ASSERT_REGISTERS(0x10, 0, 0, 0, 0, 0b00100000, 0x01, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0x0E;
    regs().f = 0b00000000;
    regs().h = 0x01;
    runOp(0x8C);
    ASSERT_REGISTERS(0x0F, 0, 0, 0, 0, 0b00000000, 0x01, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x8D", "[cpu_ops_adc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().l = 0x10;
    runOp(0x8D);
    ASSERT_REGISTERS(0xBC, 0, 0, 0, 0, 0b00000000, 0, 0x10, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0xFE;
    regs().f = 0b00010000;
    regs().l = 0x01;
    runOp(0x8D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10110000, 0, 0x01, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0x0E;
    regs().f = 0b00010000;
    regs().l = 0x01;
    runOp(0x8D);
    ASSERT_REGISTERS(0x10, 0, 0, 0, 0, 0b00100000, 0, 0x01, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0x0E;
    regs().f = 0b00000000;
    regs().l = 0x01;
    runOp(0x8D);
    ASSERT_REGISTERS(0x0F, 0, 0, 0, 0, 0b00000000, 0, 0x01, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x8E", "[cpu_ops_adc_r]")
{
    regs().a = 0xAB;
    regs().f = 0b00010000;
    regs().h = 0x12;
    regs().l = 0x34;
    mem(0x1234) = 0x10;
    runOp(0x8E);
    ASSERT_REGISTERS(0xBC, 0, 0, 0, 0, 0b00000000, 0x12, 0x34, 0, 1);
    REQUIRE(mem(0x1234) == 0x10);
    REQUIRE(ticks() == 8);

    regs().a = 0xFE;
    regs().f = 0b00010000;
    mem(0x1234) = 0x01;
    runOp(0x8E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10110000, 0x12, 0x34, 0, 2);
    REQUIRE(mem(0x1234) == 0x01);
    REQUIRE(ticks() == 16);

    regs().a = 0x0E;
    regs().f = 0b00010000;
    mem(0x1234) = 0x01;
    runOp(0x8E);
    ASSERT_REGISTERS(0x10, 0, 0, 0, 0, 0b00100000, 0x12, 0x34, 0, 3);
    REQUIRE(mem(0x1234) == 0x01);
    REQUIRE(ticks() == 24);

    regs().a = 0x0E;
    regs().f = 0b00000000;
    mem(0x1234) = 0x01;
    runOp(0x8E);
    ASSERT_REGISTERS(0x0F, 0, 0, 0, 0, 0b00000000, 0x12, 0x34, 0, 4);
    REQUIRE(mem(0x1234) == 0x01);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x8F", "[cpu_ops_adc_r]")
{
    regs().a = 0x01;
    regs().f = 0b00010000;
    runOp(0x8F);
    ASSERT_REGISTERS(0x03, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0;
    regs().f = 0b00010000;
    runOp(0x8F);
    ASSERT_REGISTERS(0x01, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xFF;
    regs().f = 0b00010000;
    runOp(0x8F);
    ASSERT_REGISTERS(0xFF, 0, 0, 0, 0, 0b00110000, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0x1F;
    regs().f = 0b00000000;
    runOp(0x8F);
    ASSERT_REGISTERS(0x3E, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);

    regs().a = 0;
    regs().f = 0b00000000;
    runOp(0x8F);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 5);
    REQUIRE(ticks() == 20);
}