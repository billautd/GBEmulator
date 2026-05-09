#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x20", "[cpu_ops_jr_cc_e]")
{
    // Z -> Do not jump
    regs().pc = 0x100;
    regs().f = 0b10000000;

    mem(0x101) = 0xAB;
    runOp(0x20);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0x102);
    REQUIRE(ticks() == 8);

    // NZ -> Jump
    regs().pc = 0x200;
    regs().f = 0b00000000;
    // Value is negative
    mem(0x201) = 0xAB;
    runOp(0x20);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0x202 + (i8)0xAB);
    REQUIRE(ticks() == 20);

    // NZ -> Jump
    regs().pc = 0x300;
    regs().f = 0b00000000;
    // Value is positive
    mem(0x301) = 0x06;
    runOp(0x20);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0x302 + (i8)0x06);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x28", "[cpu_ops_jr_cc_e]")
{
    // NZ -> Do not jump
    regs().pc = 0x100;
    regs().f = 0b00000000;

    mem(0x101) = 0xAB;
    runOp(0x28);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0x102);
    REQUIRE(ticks() == 8);

    // Z -> Jump
    regs().pc = 0x200;
    regs().f = 0b10000000;
    // Value is negative
    mem(0x201) = 0xAB;
    runOp(0x28);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0x202 + (i8)0xAB);
    REQUIRE(ticks() == 20);

    // Z -> Jump
    regs().pc = 0x300;
    regs().f = 0b10000000;
    // Value is positive
    mem(0x301) = 0x06;
    runOp(0x28);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10000000, 0, 0, 0, 0x302 + (i8)0x06);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x30", "[cpu_ops_jr_cc_e]")
{
    // C -> Do not jump
    regs().pc = 0x100;
    regs().f = 0b00010000;

    mem(0x101) = 0xAB;
    runOp(0x30);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 0x102);
    REQUIRE(ticks() == 8);

    // NC -> Jump
    regs().pc = 0x200;
    regs().f = 0b00000000;
    // Value is negative
    mem(0x201) = 0xAB;
    runOp(0x30);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0x202 + (i8)0xAB);
    REQUIRE(ticks() == 20);

    // NC -> Jump
    regs().pc = 0x300;
    regs().f = 0b00000000;
    // Value is positive
    mem(0x301) = 0x06;
    runOp(0x30);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0x302 + (i8)0x06);
    REQUIRE(ticks() == 32);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x38", "[cpu_ops_jr_cc_e]")
{
    // NC -> Do not jump
    regs().pc = 0x100;
    regs().f = 0b00000000;

    mem(0x101) = 0xAB;
    runOp(0x38);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00000000, 0, 0, 0, 0x102);
    REQUIRE(ticks() == 8);

    // C -> Jump
    regs().pc = 0x200;
    regs().f = 0b00010000;
    // Value is negative
    mem(0x201) = 0xAB;
    runOp(0x38);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 0x202 + (i8)0xAB);
    REQUIRE(ticks() == 20);

    // C -> Jump
    regs().pc = 0x300;
    regs().f = 0b00010000;
    // Value is positive
    mem(0x301) = 0x06;
    runOp(0x38);

    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00010000, 0, 0, 0, 0x302 + (i8)0x06);
    REQUIRE(ticks() == 32);
}