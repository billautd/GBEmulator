#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBC0", "[cpu_ops_set_b_r]")
{
    regs().b = 0b01001100;
    runCBPrefixOp(0xC0);
    ASSERT_REGISTERS(0, 0b01001101, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01001101;
    runCBPrefixOp(0xC0);
    ASSERT_REGISTERS(0, 0b01001101, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBC1", "[cpu_ops_set_b_r]")
{
    regs().c = 0b01001100;
    runCBPrefixOp(0xC1);
    ASSERT_REGISTERS(0, 0, 0b01001101, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01001101;
    runCBPrefixOp(0xC1);
    ASSERT_REGISTERS(0, 0, 0b01001101, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBC2", "[cpu_ops_set_b_r]")
{
    regs().d = 0b01001100;
    runCBPrefixOp(0xC2);
    ASSERT_REGISTERS(0, 0, 0, 0b01001101, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01001101;
    runCBPrefixOp(0xC2);
    ASSERT_REGISTERS(0, 0, 0, 0b01001101, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBC3", "[cpu_ops_set_b_r]")
{
    regs().e = 0b01001100;
    runCBPrefixOp(0xC3);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001101, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01001101;
    runCBPrefixOp(0xC3);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001101, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBC4", "[cpu_ops_set_b_r]")
{
    regs().h = 0b01001100;
    runCBPrefixOp(0xC4);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01001101, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01001101;
    runCBPrefixOp(0xC4);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01001101, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBC5", "[cpu_ops_set_b_r]")
{
    regs().l = 0b01001100;
    runCBPrefixOp(0xC5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001101, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01001101;
    runCBPrefixOp(0xC5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001101, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBC7", "[cpu_ops_set_b_r]")
{
    regs().a = 0b01001100;
    runCBPrefixOp(0xC7);
    ASSERT_REGISTERS(0b01001101, 0, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01001101;
    runCBPrefixOp(0xC7);
    ASSERT_REGISTERS(0b01001101, 0, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBC8", "[cpu_ops_set_b_r]")
{
    regs().b = 0b01001100;
    runCBPrefixOp(0xC8);
    ASSERT_REGISTERS(0, 0b01001110, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01001110;
    runCBPrefixOp(0xC8);
    ASSERT_REGISTERS(0, 0b01001110, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBC9", "[cpu_ops_set_b_r]")
{
    regs().c = 0b01001100;
    runCBPrefixOp(0xC9);
    ASSERT_REGISTERS(0, 0, 0b01001110, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01001110;
    runCBPrefixOp(0xC9);
    ASSERT_REGISTERS(0, 0, 0b01001110, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBCA", "[cpu_ops_set_b_r]")
{
    regs().d = 0b01001100;
    runCBPrefixOp(0xCA);
    ASSERT_REGISTERS(0, 0, 0, 0b01001110, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01001110;
    runCBPrefixOp(0xCA);
    ASSERT_REGISTERS(0, 0, 0, 0b01001110, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBCB", "[cpu_ops_set_b_r]")
{
    regs().e = 0b01001100;
    runCBPrefixOp(0xCB);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001110, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01001110;
    runCBPrefixOp(0xCB);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001110, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBCC", "[cpu_ops_set_b_r]")
{
    regs().h = 0b01001100;
    runCBPrefixOp(0xCC);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01001110, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01001110;
    runCBPrefixOp(0xCC);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01001110, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBCD", "[cpu_ops_set_b_r]")
{
    regs().l = 0b01001100;
    runCBPrefixOp(0xCD);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001110, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01001110;
    runCBPrefixOp(0xCD);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001110, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBCF", "[cpu_ops_set_b_r]")
{
    regs().a = 0b01001100;
    runCBPrefixOp(0xCF);
    ASSERT_REGISTERS(0b01001110, 0, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01001110;
    runCBPrefixOp(0xCF);
    ASSERT_REGISTERS(0b01001110, 0, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBD0", "[cpu_ops_set_b_r]")
{
    regs().b = 0b01001001;
    runCBPrefixOp(0xD0);
    ASSERT_REGISTERS(0, 0b01001101, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01001101;
    runCBPrefixOp(0xD0);
    ASSERT_REGISTERS(0, 0b01001101, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBD1", "[cpu_ops_set_b_r]")
{
    regs().c = 0b01001001;
    runCBPrefixOp(0xD1);
    ASSERT_REGISTERS(0, 0, 0b01001101, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01001101;
    runCBPrefixOp(0xD1);
    ASSERT_REGISTERS(0, 0, 0b01001101, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBD2", "[cpu_ops_set_b_r]")
{
    regs().d = 0b01001001;
    runCBPrefixOp(0xD2);
    ASSERT_REGISTERS(0, 0, 0, 0b01001101, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01001101;
    runCBPrefixOp(0xD2);
    ASSERT_REGISTERS(0, 0, 0, 0b01001101, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBD3", "[cpu_ops_set_b_r]")
{
    regs().e = 0b01001001;
    runCBPrefixOp(0xD3);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001101, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01001101;
    runCBPrefixOp(0xD3);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001101, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBD4", "[cpu_ops_set_b_r]")
{
    regs().h = 0b01001001;
    runCBPrefixOp(0xD4);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01001101, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01001101;
    runCBPrefixOp(0xD4);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01001101, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBD5", "[cpu_ops_set_b_r]")
{
    regs().l = 0b01001001;
    runCBPrefixOp(0xD5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001101, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01001101;
    runCBPrefixOp(0xD5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001101, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBD7", "[cpu_ops_set_b_r]")
{
    regs().a = 0b01001001;
    runCBPrefixOp(0xD7);
    ASSERT_REGISTERS(0b01001101, 0, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01001101;
    runCBPrefixOp(0xD7);
    ASSERT_REGISTERS(0b01001101, 0, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBD8", "[cpu_ops_set_b_r]")
{
    regs().b = 0b01000110;
    runCBPrefixOp(0xD8);
    ASSERT_REGISTERS(0, 0b01001110, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01001110;
    runCBPrefixOp(0xD8);
    ASSERT_REGISTERS(0, 0b01001110, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBD9", "[cpu_ops_set_b_r]")
{
    regs().c = 0b01001110;
    runCBPrefixOp(0xD9);
    ASSERT_REGISTERS(0, 0, 0b01001110, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01000100;
    runCBPrefixOp(0xD9);
    ASSERT_REGISTERS(0, 0, 0b01001100, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBDA", "[cpu_ops_set_b_r]")
{
    regs().d = 0b01000110;
    runCBPrefixOp(0xDA);
    ASSERT_REGISTERS(0, 0, 0, 0b01001110, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01001110;
    runCBPrefixOp(0xDA);
    ASSERT_REGISTERS(0, 0, 0, 0b01001110, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBDB", "[cpu_ops_set_b_r]")
{
    regs().e = 0b01000110;
    runCBPrefixOp(0xDB);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001110, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01001110;
    runCBPrefixOp(0xDB);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001110, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBDC", "[cpu_ops_set_b_r]")
{
    regs().h = 0b01000110;
    runCBPrefixOp(0xDC);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01001110, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01001110;
    runCBPrefixOp(0xDC);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01001110, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBDD", "[cpu_ops_set_b_r]")
{
    regs().l = 0b01000110;
    runCBPrefixOp(0xDD);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001110, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01001110;
    runCBPrefixOp(0xDD);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001110, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBDF", "[cpu_ops_set_b_r]")
{
    regs().a = 0b01000110;
    runCBPrefixOp(0xDF);
    ASSERT_REGISTERS(0b01001110, 0, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01001110;
    runCBPrefixOp(0xDF);
    ASSERT_REGISTERS(0b01001110, 0, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBE0", "[cpu_ops_set_b_r]")
{
    regs().b = 0b01001101;
    runCBPrefixOp(0xE0);
    ASSERT_REGISTERS(0, 0b01011101, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01011000;
    runCBPrefixOp(0xE0);
    ASSERT_REGISTERS(0, 0b01011000, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBE1", "[cpu_ops_set_b_r]")
{
    regs().c = 0b01001101;
    runCBPrefixOp(0xE1);
    ASSERT_REGISTERS(0, 0, 0b01011101, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01011000;
    runCBPrefixOp(0xE1);
    ASSERT_REGISTERS(0, 0, 0b01011000, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBE2", "[cpu_ops_set_b_r]")
{
    regs().d = 0b01001101;
    runCBPrefixOp(0xE2);
    ASSERT_REGISTERS(0, 0, 0, 0b01011101, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01011000;
    runCBPrefixOp(0xE2);
    ASSERT_REGISTERS(0, 0, 0, 0b01011000, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBE3", "[cpu_ops_set_b_r]")
{
    regs().e = 0b01001101;
    runCBPrefixOp(0xE3);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01011101, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01011000;
    runCBPrefixOp(0xE3);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01011000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBE4", "[cpu_ops_set_b_r]")
{
    regs().h = 0b01001101;
    runCBPrefixOp(0xE4);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01011101, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01011000;
    runCBPrefixOp(0xE4);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01011000, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBE5", "[cpu_ops_set_b_r]")
{
    regs().l = 0b01001101;
    runCBPrefixOp(0xE5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01011101, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01011000;
    runCBPrefixOp(0xE5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01011000, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBE7", "[cpu_ops_set_b_r]")
{
    regs().a = 0b01001101;
    runCBPrefixOp(0xE7);
    ASSERT_REGISTERS(0b01011101, 0, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01011000;
    runCBPrefixOp(0xE7);
    ASSERT_REGISTERS(0b01011000, 0, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBE8", "[cpu_ops_set_b_r]")
{
    regs().b = 0b01001110;
    runCBPrefixOp(0xE8);
    ASSERT_REGISTERS(0, 0b01101110, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01100100;
    runCBPrefixOp(0xE8);
    ASSERT_REGISTERS(0, 0b01100100, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBE9", "[cpu_ops_set_b_r]")
{
    regs().c = 0b01001110;
    runCBPrefixOp(0xE9);
    ASSERT_REGISTERS(0, 0, 0b01101110, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01100100;
    runCBPrefixOp(0xE9);
    ASSERT_REGISTERS(0, 0, 0b01100100, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBEA", "[cpu_ops_set_b_r]")
{
    regs().d = 0b01001110;
    runCBPrefixOp(0xEA);
    ASSERT_REGISTERS(0, 0, 0, 0b01101110, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01100100;
    runCBPrefixOp(0xEA);
    ASSERT_REGISTERS(0, 0, 0, 0b01100100, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBEB", "[cpu_ops_set_b_r]")
{
    regs().e = 0b01001110;
    runCBPrefixOp(0xEB);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01101110, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01100100;
    runCBPrefixOp(0xEB);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01100100, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBEC", "[cpu_ops_set_b_r]")
{
    regs().h = 0b01001110;
    runCBPrefixOp(0xEC);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01101110, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01100100;
    runCBPrefixOp(0xEC);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01100100, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBED", "[cpu_ops_set_b_r]")
{
    regs().l = 0b01001110;
    runCBPrefixOp(0xED);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01101110, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01100100;
    runCBPrefixOp(0xED);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01100100, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBEF", "[cpu_ops_set_b_r]")
{
    regs().a = 0b01001110;
    runCBPrefixOp(0xEF);
    ASSERT_REGISTERS(0b01101110, 0, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01100100;
    runCBPrefixOp(0xEF);
    ASSERT_REGISTERS(0b01100100, 0, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBF0", "[cpu_ops_set_b_r]")
{
    regs().b = 0b00011101;
    runCBPrefixOp(0xF0);
    ASSERT_REGISTERS(0, 0b01011101, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01001000;
    runCBPrefixOp(0xF0);
    ASSERT_REGISTERS(0, 0b01001000, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBF1", "[cpu_ops_set_b_r]")
{
    regs().c = 0b00011101;
    runCBPrefixOp(0xF1);
    ASSERT_REGISTERS(0, 0, 0b01011101, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01001000;
    runCBPrefixOp(0xF1);
    ASSERT_REGISTERS(0, 0, 0b01001000, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBF2", "[cpu_ops_set_b_r]")
{
    regs().d = 0b00011101;
    runCBPrefixOp(0xF2);
    ASSERT_REGISTERS(0, 0, 0, 0b01011101, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01001000;
    runCBPrefixOp(0xF2);
    ASSERT_REGISTERS(0, 0, 0, 0b01001000, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBF3", "[cpu_ops_set_b_r]")
{
    regs().e = 0b00011101;
    runCBPrefixOp(0xF3);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01011101, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01001000;
    runCBPrefixOp(0xF3);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBF4", "[cpu_ops_set_b_r]")
{
    regs().h = 0b00011101;
    runCBPrefixOp(0xF4);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01011101, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01001000;
    runCBPrefixOp(0xF4);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b01001000, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBF5", "[cpu_ops_set_b_r]")
{
    regs().l = 0b00011101;
    runCBPrefixOp(0xF5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01011101, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01001000;
    runCBPrefixOp(0xF5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001000, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBF7", "[cpu_ops_set_b_r]")
{
    regs().a = 0b00011101;
    runCBPrefixOp(0xF7);
    ASSERT_REGISTERS(0b01011101, 0, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01001000;
    runCBPrefixOp(0xF7);
    ASSERT_REGISTERS(0b01001000, 0, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBF8", "[cpu_ops_set_b_r]")
{
    regs().b = 0b01101110;
    runCBPrefixOp(0xF8);
    ASSERT_REGISTERS(0, 0b11101110, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b11000100;
    runCBPrefixOp(0xF8);
    ASSERT_REGISTERS(0, 0b11000100, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBF9", "[cpu_ops_set_b_r]")
{
    regs().c = 0b01101110;
    runCBPrefixOp(0xF9);
    ASSERT_REGISTERS(0, 0, 0b11101110, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b11000100;
    runCBPrefixOp(0xF9);
    ASSERT_REGISTERS(0, 0, 0b11000100, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBFA", "[cpu_ops_set_b_r]")
{
    regs().d = 0b01101110;
    runCBPrefixOp(0xFA);
    ASSERT_REGISTERS(0, 0, 0, 0b11101110, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b11000100;
    runCBPrefixOp(0xFA);
    ASSERT_REGISTERS(0, 0, 0, 0b11000100, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBFB", "[cpu_ops_set_b_r]")
{
    regs().e = 0b01101110;
    runCBPrefixOp(0xFB);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b11101110, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b11000100;
    runCBPrefixOp(0xFB);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b11000100, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBFC", "[cpu_ops_set_b_r]")
{
    regs().h = 0b01101110;
    runCBPrefixOp(0xFC);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b11101110, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b11000100;
    runCBPrefixOp(0xFC);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0b11000100, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBFD", "[cpu_ops_set_b_r]")
{
    regs().l = 0b01101110;
    runCBPrefixOp(0xFD);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b11101110, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b11000100;
    runCBPrefixOp(0xFD);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b11000100, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBFF", "[cpu_ops_set_b_r]")
{
    regs().a = 0b01101110;
    runCBPrefixOp(0xFF);
    ASSERT_REGISTERS(0b11101110, 0, 0, 0, 0, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b11000100;
    runCBPrefixOp(0xFF);
    ASSERT_REGISTERS(0b11000100, 0, 0, 0, 0, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}