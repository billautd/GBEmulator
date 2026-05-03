#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB40", "[cpu_ops_bit_b3_r8]")
{
    regs().b = 0b01001101;
    runCBPrefixOp(0x40);
    ASSERT_REGISTERS(0, 0b01001101, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01001100;
    runCBPrefixOp(0x40);
    ASSERT_REGISTERS(0, 0b01001100, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB41", "[cpu_ops_bit_b3_r8]")
{
    regs().c = 0b01001101;
    runCBPrefixOp(0x41);
    ASSERT_REGISTERS(0, 0, 0b01001101, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01001100;
    runCBPrefixOp(0x41);
    ASSERT_REGISTERS(0, 0, 0b01001100, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB42", "[cpu_ops_bit_b3_r8]")
{
    regs().d = 0b01001101;
    runCBPrefixOp(0x42);
    ASSERT_REGISTERS(0, 0, 0, 0b01001101, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01001100;
    runCBPrefixOp(0x42);
    ASSERT_REGISTERS(0, 0, 0, 0b01001100, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB43", "[cpu_ops_bit_b3_r8]")
{
    regs().e = 0b01001101;
    runCBPrefixOp(0x43);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001101, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01001100;
    runCBPrefixOp(0x43);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001100, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB44", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0b01001101;
    runCBPrefixOp(0x44);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0b01001101, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01001100;
    runCBPrefixOp(0x44);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0b01001100, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB45", "[cpu_ops_bit_b3_r8]")
{
    regs().l = 0b01001101;
    runCBPrefixOp(0x45);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0, 0b01001101, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01001100;
    runCBPrefixOp(0x45);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0b01001100, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB46", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001101;
    runCBPrefixOp(0x46);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001101);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01001100;
    runCBPrefixOp(0x46);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001100);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB47", "[cpu_ops_bit_b3_r8]")
{
    regs().a = 0b01001101;
    runCBPrefixOp(0x47);
    ASSERT_REGISTERS(0b01001101, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01001100;
    runCBPrefixOp(0x47);
    ASSERT_REGISTERS(0b01001100, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB48", "[cpu_ops_bit_b3_r8]")
{
    regs().b = 0b01001110;
    runCBPrefixOp(0x48);
    ASSERT_REGISTERS(0, 0b01001110, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01001100;
    runCBPrefixOp(0x48);
    ASSERT_REGISTERS(0, 0b01001100, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB49", "[cpu_ops_bit_b3_r8]")
{
    regs().c = 0b01001110;
    runCBPrefixOp(0x49);
    ASSERT_REGISTERS(0, 0, 0b01001110, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01001100;
    runCBPrefixOp(0x49);
    ASSERT_REGISTERS(0, 0, 0b01001100, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB4A", "[cpu_ops_bit_b3_r8]")
{
    regs().d = 0b01001110;
    runCBPrefixOp(0x4A);
    ASSERT_REGISTERS(0, 0, 0, 0b01001110, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01001100;
    runCBPrefixOp(0x4A);
    ASSERT_REGISTERS(0, 0, 0, 0b01001100, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB4B", "[cpu_ops_bit_b3_r8]")
{
    regs().e = 0b01001110;
    runCBPrefixOp(0x4B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001110, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01001100;
    runCBPrefixOp(0x4B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001100, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB4C", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0b01001110;
    runCBPrefixOp(0x4C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0b01001110, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01001100;
    runCBPrefixOp(0x4C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0b01001100, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB4D", "[cpu_ops_bit_b3_r8]")
{
    regs().l = 0b01001110;
    runCBPrefixOp(0x4D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0, 0b01001110, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01001100;
    runCBPrefixOp(0x4D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0b01001100, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB4E", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001110;
    runCBPrefixOp(0x4E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001110);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01001100;
    runCBPrefixOp(0x4E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001100);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB4F", "[cpu_ops_bit_b3_r8]")
{
    regs().a = 0b01001110;
    runCBPrefixOp(0x4F);
    ASSERT_REGISTERS(0b01001110, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01001100;
    runCBPrefixOp(0x4F);
    ASSERT_REGISTERS(0b01001100, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB50", "[cpu_ops_bit_b3_r8]")
{
    regs().b = 0b01001101;
    runCBPrefixOp(0x50);
    ASSERT_REGISTERS(0, 0b01001101, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01001000;
    runCBPrefixOp(0x50);
    ASSERT_REGISTERS(0, 0b01001000, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB51", "[cpu_ops_bit_b3_r8]")
{
    regs().c = 0b01001101;
    runCBPrefixOp(0x51);
    ASSERT_REGISTERS(0, 0, 0b01001101, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01001000;
    runCBPrefixOp(0x51);
    ASSERT_REGISTERS(0, 0, 0b01001000, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB52", "[cpu_ops_bit_b3_r8]")
{
    regs().d = 0b01001101;
    runCBPrefixOp(0x52);
    ASSERT_REGISTERS(0, 0, 0, 0b01001101, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01001000;
    runCBPrefixOp(0x52);
    ASSERT_REGISTERS(0, 0, 0, 0b01001000, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB53", "[cpu_ops_bit_b3_r8]")
{
    regs().e = 0b01001101;
    runCBPrefixOp(0x53);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001101, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01001000;
    runCBPrefixOp(0x53);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001000, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB54", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0b01001101;
    runCBPrefixOp(0x54);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0b01001101, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01001000;
    runCBPrefixOp(0x54);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0b01001000, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB55", "[cpu_ops_bit_b3_r8]")
{
    regs().l = 0b01001101;
    runCBPrefixOp(0x55);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0, 0b01001101, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01001000;
    runCBPrefixOp(0x55);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0b01001000, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB56", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001101;
    runCBPrefixOp(0x56);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001101);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01001000;
    runCBPrefixOp(0x56);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001000);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB57", "[cpu_ops_bit_b3_r8]")
{
    regs().a = 0b01001101;
    runCBPrefixOp(0x57);
    ASSERT_REGISTERS(0b01001101, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01001000;
    runCBPrefixOp(0x57);
    ASSERT_REGISTERS(0b01001000, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB58", "[cpu_ops_bit_b3_r8]")
{
    regs().b = 0b01001110;
    runCBPrefixOp(0x58);
    ASSERT_REGISTERS(0, 0b01001110, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01000100;
    runCBPrefixOp(0x58);
    ASSERT_REGISTERS(0, 0b01000100, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB59", "[cpu_ops_bit_b3_r8]")
{
    regs().c = 0b01001110;
    runCBPrefixOp(0x59);
    ASSERT_REGISTERS(0, 0, 0b01001110, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01000100;
    runCBPrefixOp(0x59);
    ASSERT_REGISTERS(0, 0, 0b01000100, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB5A", "[cpu_ops_bit_b3_r8]")
{
    regs().d = 0b01001110;
    runCBPrefixOp(0x5A);
    ASSERT_REGISTERS(0, 0, 0, 0b01001110, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01000100;
    runCBPrefixOp(0x5A);
    ASSERT_REGISTERS(0, 0, 0, 0b01000100, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB5B", "[cpu_ops_bit_b3_r8]")
{
    regs().e = 0b01001110;
    runCBPrefixOp(0x5B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001110, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01000100;
    runCBPrefixOp(0x5B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01000100, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB5C", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0b01001110;
    runCBPrefixOp(0x5C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0b01001110, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01000100;
    runCBPrefixOp(0x5C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0b01000100, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB5D", "[cpu_ops_bit_b3_r8]")
{
    regs().l = 0b01001110;
    runCBPrefixOp(0x5D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0, 0b01001110, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01000100;
    runCBPrefixOp(0x5D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0b01000100, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB5E", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001110;
    runCBPrefixOp(0x5E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001110);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01000100;
    runCBPrefixOp(0x5E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01000100);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB5F", "[cpu_ops_bit_b3_r8]")
{
    regs().a = 0b01001110;
    runCBPrefixOp(0x5F);
    ASSERT_REGISTERS(0b01001110, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01000100;
    runCBPrefixOp(0x5F);
    ASSERT_REGISTERS(0b01000100, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB60", "[cpu_ops_bit_b3_r8]")
{
    regs().b = 0b01011101;
    runCBPrefixOp(0x60);
    ASSERT_REGISTERS(0, 0b01011101, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01001000;
    runCBPrefixOp(0x60);
    ASSERT_REGISTERS(0, 0b01001000, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB61", "[cpu_ops_bit_b3_r8]")
{
    regs().c = 0b01011101;
    runCBPrefixOp(0x61);
    ASSERT_REGISTERS(0, 0, 0b01011101, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01001000;
    runCBPrefixOp(0x61);
    ASSERT_REGISTERS(0, 0, 0b01001000, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB62", "[cpu_ops_bit_b3_r8]")
{
    regs().d = 0b01011101;
    runCBPrefixOp(0x62);
    ASSERT_REGISTERS(0, 0, 0, 0b01011101, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01001000;
    runCBPrefixOp(0x62);
    ASSERT_REGISTERS(0, 0, 0, 0b01001000, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB63", "[cpu_ops_bit_b3_r8]")
{
    regs().e = 0b01011101;
    runCBPrefixOp(0x63);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01011101, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01001000;
    runCBPrefixOp(0x63);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001000, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB64", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0b01011101;
    runCBPrefixOp(0x64);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0b01011101, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01001000;
    runCBPrefixOp(0x64);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0b01001000, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB65", "[cpu_ops_bit_b3_r8]")
{
    regs().l = 0b01011101;
    runCBPrefixOp(0x65);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0, 0b01011101, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01001000;
    runCBPrefixOp(0x65);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0b01001000, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB66", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01011101;
    runCBPrefixOp(0x66);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01011101);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01001000;
    runCBPrefixOp(0x66);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001000);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB67", "[cpu_ops_bit_b3_r8]")
{
    regs().a = 0b01011101;
    runCBPrefixOp(0x67);
    ASSERT_REGISTERS(0b01011101, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01001000;
    runCBPrefixOp(0x67);
    ASSERT_REGISTERS(0b01001000, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB68", "[cpu_ops_bit_b3_r8]")
{
    regs().b = 0b01101110;
    runCBPrefixOp(0x68);
    ASSERT_REGISTERS(0, 0b01101110, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01000100;
    runCBPrefixOp(0x68);
    ASSERT_REGISTERS(0, 0b01000100, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB69", "[cpu_ops_bit_b3_r8]")
{
    regs().c = 0b01101110;
    runCBPrefixOp(0x69);
    ASSERT_REGISTERS(0, 0, 0b01101110, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01000100;
    runCBPrefixOp(0x69);
    ASSERT_REGISTERS(0, 0, 0b01000100, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB6A", "[cpu_ops_bit_b3_r8]")
{
    regs().d = 0b01101110;
    runCBPrefixOp(0x6A);
    ASSERT_REGISTERS(0, 0, 0, 0b01101110, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01000100;
    runCBPrefixOp(0x6A);
    ASSERT_REGISTERS(0, 0, 0, 0b01000100, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB6B", "[cpu_ops_bit_b3_r8]")
{
    regs().e = 0b01101110;
    runCBPrefixOp(0x6B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01101110, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01000100;
    runCBPrefixOp(0x6B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01000100, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB6C", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0b01101110;
    runCBPrefixOp(0x6C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0b01101110, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01000100;
    runCBPrefixOp(0x6C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0b01000100, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB6D", "[cpu_ops_bit_b3_r8]")
{
    regs().l = 0b01101110;
    runCBPrefixOp(0x6D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0, 0b01101110, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01000100;
    runCBPrefixOp(0x6D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0b01000100, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB6E", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01101110;
    runCBPrefixOp(0x6E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01101110);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01000100;
    runCBPrefixOp(0x6E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01000100);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB6F", "[cpu_ops_bit_b3_r8]")
{
    regs().a = 0b01101110;
    runCBPrefixOp(0x6F);
    ASSERT_REGISTERS(0b01101110, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01000100;
    runCBPrefixOp(0x6F);
    ASSERT_REGISTERS(0b01000100, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB70", "[cpu_ops_bit_b3_r8]")
{
    regs().b = 0b01011101;
    runCBPrefixOp(0x70);
    ASSERT_REGISTERS(0, 0b01011101, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b00001000;
    runCBPrefixOp(0x70);
    ASSERT_REGISTERS(0, 0b00001000, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB71", "[cpu_ops_bit_b3_r8]")
{
    regs().c = 0b01011101;
    runCBPrefixOp(0x71);
    ASSERT_REGISTERS(0, 0, 0b01011101, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b00001000;
    runCBPrefixOp(0x71);
    ASSERT_REGISTERS(0, 0, 0b00001000, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB72", "[cpu_ops_bit_b3_r8]")
{
    regs().d = 0b01011101;
    runCBPrefixOp(0x72);
    ASSERT_REGISTERS(0, 0, 0, 0b01011101, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b00001000;
    runCBPrefixOp(0x72);
    ASSERT_REGISTERS(0, 0, 0, 0b00001000, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB73", "[cpu_ops_bit_b3_r8]")
{
    regs().e = 0b01011101;
    runCBPrefixOp(0x73);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01011101, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b00001000;
    runCBPrefixOp(0x73);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b00001000, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB74", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0b01011101;
    runCBPrefixOp(0x74);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0b01011101, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b00001000;
    runCBPrefixOp(0x74);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0b00001000, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB75", "[cpu_ops_bit_b3_r8]")
{
    regs().l = 0b01011101;
    runCBPrefixOp(0x75);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0, 0b01011101, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b00001000;
    runCBPrefixOp(0x75);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0b00001000, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB76", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01011101;
    runCBPrefixOp(0x76);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01011101);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b00001000;
    runCBPrefixOp(0x76);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b00001000);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB77", "[cpu_ops_bit_b3_r8]")
{
    regs().a = 0b01011101;
    runCBPrefixOp(0x77);
    ASSERT_REGISTERS(0b01011101, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b00001000;
    runCBPrefixOp(0x77);
    ASSERT_REGISTERS(0b00001000, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB78", "[cpu_ops_bit_b3_r8]")
{
    regs().b = 0b11101110;
    runCBPrefixOp(0x78);
    ASSERT_REGISTERS(0, 0b11101110, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0b01000100;
    runCBPrefixOp(0x78);
    ASSERT_REGISTERS(0, 0b01000100, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB79", "[cpu_ops_bit_b3_r8]")
{
    regs().c = 0b11101110;
    runCBPrefixOp(0x79);
    ASSERT_REGISTERS(0, 0, 0b11101110, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0b01000100;
    runCBPrefixOp(0x79);
    ASSERT_REGISTERS(0, 0, 0b01000100, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB7A", "[cpu_ops_bit_b3_r8]")
{
    regs().d = 0b11101110;
    runCBPrefixOp(0x7A);
    ASSERT_REGISTERS(0, 0, 0, 0b11101110, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0b01000100;
    runCBPrefixOp(0x7A);
    ASSERT_REGISTERS(0, 0, 0, 0b01000100, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB7B", "[cpu_ops_bit_b3_r8]")
{
    regs().e = 0b11101110;
    runCBPrefixOp(0x7B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b11101110, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0b01000100;
    runCBPrefixOp(0x7B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01000100, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB7C", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0b11101110;
    runCBPrefixOp(0x7C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0b11101110, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0b01000100;
    runCBPrefixOp(0x7C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0b01000100, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB7D", "[cpu_ops_bit_b3_r8]")
{
    regs().l = 0b11101110;
    runCBPrefixOp(0x7D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0, 0b11101110, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0b01000100;
    runCBPrefixOp(0x7D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0, 0b01000100, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB7E", "[cpu_ops_bit_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b11101110;
    runCBPrefixOp(0x7E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b00100000, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b11101110);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0b01000100;
    runCBPrefixOp(0x7E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b10100000, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01000100);
    REQUIRE(ticks() == 24);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB7F", "[cpu_ops_bit_b3_r8]")
{
    regs().a = 0b11101110;
    runCBPrefixOp(0x7F);
    ASSERT_REGISTERS(0b11101110, 0, 0, 0, 0, 0b00100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0b01000100;
    runCBPrefixOp(0x7F);
    ASSERT_REGISTERS(0b01000100, 0, 0, 0, 0, 0b10100000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}