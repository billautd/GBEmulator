#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB46", "[cpu_ops_bit_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001101;
    runCBPrefixOp(0x46);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001101);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01001100;
    runCBPrefixOp(0x46);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001100);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB4E", "[cpu_ops_bit_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001110;
    runCBPrefixOp(0x4E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001110);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01001100;
    runCBPrefixOp(0x4E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001100);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB56", "[cpu_ops_bit_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001101;
    runCBPrefixOp(0x56);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001101);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01001000;
    runCBPrefixOp(0x56);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001000);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB5E", "[cpu_ops_bit_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001110;
    runCBPrefixOp(0x5E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001110);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01000100;
    runCBPrefixOp(0x5E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01000100);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB66", "[cpu_ops_bit_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01011101;
    runCBPrefixOp(0x66);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01011101);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01001000;
    runCBPrefixOp(0x66);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001000);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB6E", "[cpu_ops_bit_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01101110;
    runCBPrefixOp(0x6E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01101110);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01000100;
    runCBPrefixOp(0x6E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01000100);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB76", "[cpu_ops_bit_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01011101;
    runCBPrefixOp(0x76);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01011101);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b00001000;
    runCBPrefixOp(0x76);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b00001000);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB7E", "[cpu_ops_bit_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b11101110;
    runCBPrefixOp(0x7E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b11101110);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01000100;
    runCBPrefixOp(0x7E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01000100);
    REQUIRE(ticks() == 24);
}