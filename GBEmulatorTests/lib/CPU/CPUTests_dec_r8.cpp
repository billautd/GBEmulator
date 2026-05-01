#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x05", "[cpu_ops_dec_r8]")
{
    regs().b = 0x12;
    runOp(0x05);
    ASSERT_REGISTERS(0, 0x11, 0, 0, 0, 0b01000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().b = 0x00;
    runOp(0x05);
    ASSERT_REGISTERS(0, 0xFF, 0, 0, 0, 0b01100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().b = 0xA0;
    runOp(0x05);
    ASSERT_REGISTERS(0, 0x9F, 0, 0, 0, 0b01100000, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().b = 0x01;
    runOp(0x05);
    ASSERT_REGISTERS(0, 0x00, 0, 0, 0, 0b11000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x0D", "[cpu_ops_dec_r8]")
{
    regs().c = 0x12;
    runOp(0x0D);
    ASSERT_REGISTERS(0, 0, 0x11, 0, 0, 0b01000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().c = 0x00;
    runOp(0x0D);
    ASSERT_REGISTERS(0, 0, 0xFF, 0, 0, 0b01100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().c = 0xA0;
    runOp(0x0D);
    ASSERT_REGISTERS(0, 0, 0x9F, 0, 0, 0b01100000, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().c = 0x01;
    runOp(0x0D);
    ASSERT_REGISTERS(0, 0, 0x00, 0, 0, 0b11000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x15", "[cpu_ops_dec_r8]")
{
    regs().d = 0x12;
    runOp(0x15);
    ASSERT_REGISTERS(0, 0, 0, 0x11, 0, 0b01000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().d = 0x00;
    runOp(0x15);
    ASSERT_REGISTERS(0, 0, 0, 0xFF, 0, 0b01100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().d = 0xA0;
    runOp(0x15);
    ASSERT_REGISTERS(0, 0, 0, 0x9F, 0, 0b01100000, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().d = 0x01;
    runOp(0x15);
    ASSERT_REGISTERS(0, 0, 0, 0x00, 0, 0b11000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x1D", "[cpu_ops_dec_r8]")
{
    regs().e = 0x12;
    runOp(0x1D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x11, 0b01000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().e = 0x00;
    runOp(0x1D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0xFF, 0b01100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().e = 0xA0;
    runOp(0x1D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x9F, 0b01100000, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().e = 0x01;
    runOp(0x1D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0x00, 0b11000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x25", "[cpu_ops_dec_r8]")
{
    regs().h = 0x12;
    runOp(0x25);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b01000000, 0, 0x11, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().h = 0x00;
    runOp(0x25);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b01100000, 0, 0xFF, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().h = 0xA0;
    runOp(0x25);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b01100000, 0, 0x9F, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().h = 0x01;
    runOp(0x25);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b11000000, 0, 0x00, 0, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x2D", "[cpu_ops_dec_r8]")
{
    regs().l = 0x12;
    runOp(0x2D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b01000000, 0, 0, 0x11, 0, 1);
    REQUIRE(ticks() == 4);

    regs().l = 0x00;
    runOp(0x2D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b01100000, 0, 0, 0xFF, 0, 2);
    REQUIRE(ticks() == 8);

    regs().l = 0xA0;
    runOp(0x2D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b01100000, 0, 0, 0x9F, 0, 3);
    REQUIRE(ticks() == 12);

    regs().l = 0x01;
    runOp(0x2D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b11000000, 0, 0, 0x00, 0, 4);
    REQUIRE(ticks() == 16);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x35", "[cpu_ops_dec_r8]")
{
    // Byte pointed to
    regs().h = 0xAB;
    regs().l = 0xCD;

    mem(0xABCD) = 0x12;
    runOp(0x35);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b01000000, 0, 0xAB, 0xCD, 0, 1);
    REQUIRE(mem(0xABCD) == 0x11);
    REQUIRE(ticks() == 12);

    mem(0xABCD) = 0x00;
    runOp(0x35);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b01100000, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0xFF);
    REQUIRE(ticks() == 24);

    mem(0xABCD) = 0xA0;
    runOp(0x35);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b01100000, 0, 0xAB, 0xCD, 0, 3);
    REQUIRE(mem(0xABCD) == 0x9F);
    REQUIRE(ticks() == 36);

    mem(0xABCD) = 0x01;
    runOp(0x35);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0b11000000, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0x00);
    REQUIRE(ticks() == 48);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x3D", "[cpu_ops_dec_r8]")
{
    regs().a = 0x12;
    runOp(0x3D);
    ASSERT_REGISTERS(0x11, 0, 0, 0, 0, 0b01000000, 0, 0, 0, 0, 1);
    REQUIRE(ticks() == 4);

    regs().a = 0x00;
    runOp(0x3D);
    ASSERT_REGISTERS(0xFF, 0, 0, 0, 0, 0b01100000, 0, 0, 0, 0, 2);
    REQUIRE(ticks() == 8);

    regs().a = 0xA0;
    runOp(0x3D);
    ASSERT_REGISTERS(0x9F, 0, 0, 0, 0, 0b01100000, 0, 0, 0, 0, 3);
    REQUIRE(ticks() == 12);

    regs().a = 0x01;
    runOp(0x3D);
    ASSERT_REGISTERS(0x00, 0, 0, 0, 0, 0b11000000, 0, 0, 0, 0, 4);
    REQUIRE(ticks() == 16);
}