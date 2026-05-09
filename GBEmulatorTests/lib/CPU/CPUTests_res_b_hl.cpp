#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB86", "[cpu_ops_res_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001101;
    runCBPrefixOp(0x86);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001100);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01001100;
    runCBPrefixOp(0x86);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001100);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB8E", "[cpu_ops_res_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001110;
    runCBPrefixOp(0x8E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001100);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01001100;
    runCBPrefixOp(0x8E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001100);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB96", "[cpu_ops_res_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001101;
    runCBPrefixOp(0x96);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001001);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01001000;
    runCBPrefixOp(0x96);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001000);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB9E", "[cpu_ops_res_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001110;
    runCBPrefixOp(0x9E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01000110);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01000100;
    runCBPrefixOp(0x9E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01000100);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBA6", "[cpu_ops_res_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01011101;
    runCBPrefixOp(0xA6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001101);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01001000;
    runCBPrefixOp(0xA6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001000);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBAE", "[cpu_ops_res_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01101110;
    runCBPrefixOp(0xAE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001110);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01000100;
    runCBPrefixOp(0xAE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01000100);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBB6", "[cpu_ops_res_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01011101;
    runCBPrefixOp(0xB6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b00011101);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b00001000;
    runCBPrefixOp(0xB6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b00001000);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBBE", "[cpu_ops_res_b_hl]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b11101110;
    runCBPrefixOp(0xBE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01101110);
    REQUIRE(ticks() == 16);

    mem(0xABCD) = 0b01000100;
    runCBPrefixOp(0xBE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01000100);
    REQUIRE(ticks() == 32);
}