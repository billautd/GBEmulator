#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBC6", "[cpu_ops_set_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001100;
    runCBPrefixOp(0xC6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001101);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01001101;
    runCBPrefixOp(0xC6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001101);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBCE", "[cpu_ops_set_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001100;
    runCBPrefixOp(0xCE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001110);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01001110;
    runCBPrefixOp(0xCE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001110);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBD6", "[cpu_ops_set_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001001;
    runCBPrefixOp(0xD6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001101);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01001100;
    runCBPrefixOp(0xD6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001100);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBDE", "[cpu_ops_set_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01000110;
    runCBPrefixOp(0xDE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001110);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01001100;
    runCBPrefixOp(0xDE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001100);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBE6", "[cpu_ops_set_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001101;
    runCBPrefixOp(0xE6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01011101);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01011000;
    runCBPrefixOp(0xE6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01011000);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBEE", "[cpu_ops_set_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01011110;
    runCBPrefixOp(0xEE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01111110);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01110100;
    runCBPrefixOp(0xEE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01110100);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBF6", "[cpu_ops_set_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b00011101;
    runCBPrefixOp(0xF6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01011101);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01001000;
    runCBPrefixOp(0xF6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001000);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBFE", "[cpu_ops_set_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01101110;
    runCBPrefixOp(0xFE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b11101110);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b11000100;
    runCBPrefixOp(0xFE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b11000100);
    REQUIRE(ticks() == 32);
}