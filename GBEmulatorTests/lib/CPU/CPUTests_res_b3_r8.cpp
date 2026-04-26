#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB80", "[cpu_ops_res_b3_r8]")
{
    regs().b = 0b01001101;
    runCBPrefixOp(0x80);
    ASSERT_REGISTERS(0, 0b01001100, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().b = 0b01001100;
    runCBPrefixOp(0x80);
    ASSERT_REGISTERS(0, 0b01001100, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB81", "[cpu_ops_res_b3_r8]")
{
    regs().c = 0b01001101;
    runCBPrefixOp(0x81);
    ASSERT_REGISTERS(0, 0, 0b01001100, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().c = 0b01001100;
    runCBPrefixOp(0x81);
    ASSERT_REGISTERS(0, 0, 0b01001100, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB82", "[cpu_ops_res_b3_r8]")
{
    regs().d = 0b01001101;
    runCBPrefixOp(0x82);
    ASSERT_REGISTERS(0, 0, 0, 0b01001100, 0, 0, 0, 0, 0, 0, 2);

    regs().d = 0b01001100;
    runCBPrefixOp(0x82);
    ASSERT_REGISTERS(0, 0, 0, 0b01001100, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB83", "[cpu_ops_res_b3_r8]")
{
    regs().e = 0b01001101;
    runCBPrefixOp(0x83);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001100, 0, 0, 0, 0, 0, 2);

    regs().e = 0b01001100;
    runCBPrefixOp(0x83);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001100, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB84", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0b01001101;
    runCBPrefixOp(0x84);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001100, 0, 0, 2);

    regs().h = 0b01001100;
    runCBPrefixOp(0x84);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001100, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB85", "[cpu_ops_res_b3_r8]")
{
    regs().l = 0b01001101;
    runCBPrefixOp(0x85);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01001100, 0, 2);

    regs().l = 0b01001100;
    runCBPrefixOp(0x85);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01001100, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB86", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001101;
    runCBPrefixOp(0x86);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001100);

    mem(0xABCD) = 0b01001100;
    runCBPrefixOp(0x86);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001100);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB87", "[cpu_ops_res_b3_r8]")
{
    regs().a = 0b01001101;
    runCBPrefixOp(0x87);
    ASSERT_REGISTERS(0b01001100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().a = 0b01001100;
    runCBPrefixOp(0x87);
    ASSERT_REGISTERS(0b01001100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB88", "[cpu_ops_res_b3_r8]")
{
    regs().b = 0b01001110;
    runCBPrefixOp(0x88);
    ASSERT_REGISTERS(0, 0b01001100, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().b = 0b01001100;
    runCBPrefixOp(0x88);
    ASSERT_REGISTERS(0, 0b01001100, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB89", "[cpu_ops_res_b3_r8]")
{
    regs().c = 0b01001110;
    runCBPrefixOp(0x89);
    ASSERT_REGISTERS(0, 0, 0b01001100, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().c = 0b01001100;
    runCBPrefixOp(0x89);
    ASSERT_REGISTERS(0, 0, 0b01001100, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB8A", "[cpu_ops_res_b3_r8]")
{
    regs().d = 0b01001110;
    runCBPrefixOp(0x8A);
    ASSERT_REGISTERS(0, 0, 0, 0b01001100, 0, 0, 0, 0, 0, 0, 2);

    regs().d = 0b01001100;
    runCBPrefixOp(0x8A);
    ASSERT_REGISTERS(0, 0, 0, 0b01001100, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB8B", "[cpu_ops_res_b3_r8]")
{
    regs().e = 0b01001110;
    runCBPrefixOp(0x8B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001100, 0, 0, 0, 0, 0, 2);

    regs().e = 0b01001100;
    runCBPrefixOp(0x8B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001100, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB8C", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0b01001110;
    runCBPrefixOp(0x8C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001100, 0, 0, 2);

    regs().h = 0b01001100;
    runCBPrefixOp(0x8C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001100, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB8D", "[cpu_ops_res_b3_r8]")
{
    regs().l = 0b01001110;
    runCBPrefixOp(0x8D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01001100, 0, 2);

    regs().l = 0b01001100;
    runCBPrefixOp(0x8D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01001100, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB8E", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001110;
    runCBPrefixOp(0x8E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001100);

    mem(0xABCD) = 0b01001100;
    runCBPrefixOp(0x8E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001100);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB8F", "[cpu_ops_res_b3_r8]")
{
    regs().a = 0b01001110;
    runCBPrefixOp(0x8F);
    ASSERT_REGISTERS(0b01001100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().a = 0b01001100;
    runCBPrefixOp(0x8F);
    ASSERT_REGISTERS(0b01001100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB90", "[cpu_ops_res_b3_r8]")
{
    regs().b = 0b01001101;
    runCBPrefixOp(0x90);
    ASSERT_REGISTERS(0, 0b01001001, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().b = 0b01001000;
    runCBPrefixOp(0x90);
    ASSERT_REGISTERS(0, 0b01001000, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB91", "[cpu_ops_res_b3_r8]")
{
    regs().c = 0b01001101;
    runCBPrefixOp(0x91);
    ASSERT_REGISTERS(0, 0, 0b01001001, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().c = 0b01001000;
    runCBPrefixOp(0x91);
    ASSERT_REGISTERS(0, 0, 0b01001000, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB92", "[cpu_ops_res_b3_r8]")
{
    regs().d = 0b01001101;
    runCBPrefixOp(0x92);
    ASSERT_REGISTERS(0, 0, 0, 0b01001001, 0, 0, 0, 0, 0, 0, 2);

    regs().d = 0b01001000;
    runCBPrefixOp(0x92);
    ASSERT_REGISTERS(0, 0, 0, 0b01001000, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB93", "[cpu_ops_res_b3_r8]")
{
    regs().e = 0b01001101;
    runCBPrefixOp(0x93);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001001, 0, 0, 0, 0, 0, 2);

    regs().e = 0b01001000;
    runCBPrefixOp(0x93);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001000, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB94", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0b01001101;
    runCBPrefixOp(0x94);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001001, 0, 0, 2);

    regs().h = 0b01001000;
    runCBPrefixOp(0x94);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001000, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB95", "[cpu_ops_res_b3_r8]")
{
    regs().l = 0b01001101;
    runCBPrefixOp(0x95);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01001001, 0, 2);

    regs().l = 0b01001000;
    runCBPrefixOp(0x95);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01001000, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB96", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001101;
    runCBPrefixOp(0x96);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001001);

    mem(0xABCD) = 0b01001000;
    runCBPrefixOp(0x96);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001000);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB97", "[cpu_ops_res_b3_r8]")
{
    regs().a = 0b01001101;
    runCBPrefixOp(0x97);
    ASSERT_REGISTERS(0b01001001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().a = 0b01001000;
    runCBPrefixOp(0x97);
    ASSERT_REGISTERS(0b01001000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB98", "[cpu_ops_res_b3_r8]")
{
    regs().b = 0b01001110;
    runCBPrefixOp(0x98);
    ASSERT_REGISTERS(0, 0b01000110, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().b = 0b01000100;
    runCBPrefixOp(0x98);
    ASSERT_REGISTERS(0, 0b01000100, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB99", "[cpu_ops_res_b3_r8]")
{
    regs().c = 0b01001110;
    runCBPrefixOp(0x99);
    ASSERT_REGISTERS(0, 0, 0b01000110, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().c = 0b01000100;
    runCBPrefixOp(0x99);
    ASSERT_REGISTERS(0, 0, 0b01000100, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB9A", "[cpu_ops_res_b3_r8]")
{
    regs().d = 0b01001110;
    runCBPrefixOp(0x9A);
    ASSERT_REGISTERS(0, 0, 0, 0b01000110, 0, 0, 0, 0, 0, 0, 2);

    regs().d = 0b01000100;
    runCBPrefixOp(0x9A);
    ASSERT_REGISTERS(0, 0, 0, 0b01000100, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB9B", "[cpu_ops_res_b3_r8]")
{
    regs().e = 0b01001110;
    runCBPrefixOp(0x9B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01000110, 0, 0, 0, 0, 0, 2);

    regs().e = 0b01000100;
    runCBPrefixOp(0x9B);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01000100, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB9C", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0b01001110;
    runCBPrefixOp(0x9C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01000110, 0, 0, 2);

    regs().h = 0b01000100;
    runCBPrefixOp(0x9C);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01000100, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB9D", "[cpu_ops_res_b3_r8]")
{
    regs().l = 0b01001110;
    runCBPrefixOp(0x9D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01000110, 0, 2);

    regs().l = 0b01000100;
    runCBPrefixOp(0x9D);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01000100, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB9E", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01001110;
    runCBPrefixOp(0x9E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01000110);

    mem(0xABCD) = 0b01000100;
    runCBPrefixOp(0x9E);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01000100);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCB9F", "[cpu_ops_res_b3_r8]")
{
    regs().a = 0b01001110;
    runCBPrefixOp(0x9F);
    ASSERT_REGISTERS(0b01000110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().a = 0b01000100;
    runCBPrefixOp(0x9F);
    ASSERT_REGISTERS(0b01000100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBA0", "[cpu_ops_res_b3_r8]")
{
    regs().b = 0b01011101;
    runCBPrefixOp(0xA0);
    ASSERT_REGISTERS(0, 0b01001101, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().b = 0b01001000;
    runCBPrefixOp(0xA0);
    ASSERT_REGISTERS(0, 0b01001000, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBA1", "[cpu_ops_res_b3_r8]")
{
    regs().c = 0b01011101;
    runCBPrefixOp(0xA1);
    ASSERT_REGISTERS(0, 0, 0b01001101, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().c = 0b01001000;
    runCBPrefixOp(0xA1);
    ASSERT_REGISTERS(0, 0, 0b01001000, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBA2", "[cpu_ops_res_b3_r8]")
{
    regs().d = 0b01011101;
    runCBPrefixOp(0xA2);
    ASSERT_REGISTERS(0, 0, 0, 0b01001101, 0, 0, 0, 0, 0, 0, 2);

    regs().d = 0b01001000;
    runCBPrefixOp(0xA2);
    ASSERT_REGISTERS(0, 0, 0, 0b01001000, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBA3", "[cpu_ops_res_b3_r8]")
{
    regs().e = 0b01011101;
    runCBPrefixOp(0xA3);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001101, 0, 0, 0, 0, 0, 2);

    regs().e = 0b01001000;
    runCBPrefixOp(0xA3);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001000, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBA4", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0b01011101;
    runCBPrefixOp(0xA4);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001101, 0, 0, 2);

    regs().h = 0b01001000;
    runCBPrefixOp(0xA4);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001000, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBA5", "[cpu_ops_res_b3_r8]")
{
    regs().l = 0b01011101;
    runCBPrefixOp(0xA5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01001101, 0, 2);

    regs().l = 0b01001000;
    runCBPrefixOp(0xA5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01001000, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBA6", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01011101;
    runCBPrefixOp(0xA6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001101);

    mem(0xABCD) = 0b01001000;
    runCBPrefixOp(0xA6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01001000);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBA7", "[cpu_ops_res_b3_r8]")
{
    regs().a = 0b01011101;
    runCBPrefixOp(0xA7);
    ASSERT_REGISTERS(0b01001101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().a = 0b01001000;
    runCBPrefixOp(0xA7);
    ASSERT_REGISTERS(0b01001000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBA8", "[cpu_ops_res_b3_r8]")
{
    regs().b = 0b01101110;
    runCBPrefixOp(0xA8);
    ASSERT_REGISTERS(0, 0b01001110, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().b = 0b01000100;
    runCBPrefixOp(0xA8);
    ASSERT_REGISTERS(0, 0b01000100, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBA9", "[cpu_ops_res_b3_r8]")
{
    regs().c = 0b01101110;
    runCBPrefixOp(0xA9);
    ASSERT_REGISTERS(0, 0, 0b01001110, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().c = 0b01000100;
    runCBPrefixOp(0xA9);
    ASSERT_REGISTERS(0, 0, 0b01000100, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBAA", "[cpu_ops_res_b3_r8]")
{
    regs().d = 0b01101110;
    runCBPrefixOp(0xAA);
    ASSERT_REGISTERS(0, 0, 0, 0b01001110, 0, 0, 0, 0, 0, 0, 2);

    regs().d = 0b01000100;
    runCBPrefixOp(0xAA);
    ASSERT_REGISTERS(0, 0, 0, 0b01000100, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBAB", "[cpu_ops_res_b3_r8]")
{
    regs().e = 0b01101110;
    runCBPrefixOp(0xAB);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01001110, 0, 0, 0, 0, 0, 2);

    regs().e = 0b01000100;
    runCBPrefixOp(0xAB);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01000100, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBAC", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0b01101110;
    runCBPrefixOp(0xAC);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01001110, 0, 0, 2);

    regs().h = 0b01000100;
    runCBPrefixOp(0xAC);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01000100, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBAD", "[cpu_ops_res_b3_r8]")
{
    regs().l = 0b01101110;
    runCBPrefixOp(0xAD);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01001110, 0, 2);

    regs().l = 0b01000100;
    runCBPrefixOp(0xAD);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01000100, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBAE", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01101110;
    runCBPrefixOp(0xAE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01001110);

    mem(0xABCD) = 0b01000100;
    runCBPrefixOp(0xAE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01000100);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBAF", "[cpu_ops_res_b3_r8]")
{
    regs().a = 0b01101110;
    runCBPrefixOp(0xAF);
    ASSERT_REGISTERS(0b01001110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().a = 0b01000100;
    runCBPrefixOp(0xAF);
    ASSERT_REGISTERS(0b01000100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBB0", "[cpu_ops_res_b3_r8]")
{
    regs().b = 0b01011101;
    runCBPrefixOp(0xB0);
    ASSERT_REGISTERS(0, 0b00011101, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().b = 0b00001000;
    runCBPrefixOp(0xB0);
    ASSERT_REGISTERS(0, 0b00001000, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBB1", "[cpu_ops_res_b3_r8]")
{
    regs().c = 0b01011101;
    runCBPrefixOp(0xB1);
    ASSERT_REGISTERS(0, 0, 0b00011101, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().c = 0b00001000;
    runCBPrefixOp(0xB1);
    ASSERT_REGISTERS(0, 0, 0b00001000, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBB2", "[cpu_ops_res_b3_r8]")
{
    regs().d = 0b01011101;
    runCBPrefixOp(0xB2);
    ASSERT_REGISTERS(0, 0, 0, 0b00011101, 0, 0, 0, 0, 0, 0, 2);

    regs().d = 0b00001000;
    runCBPrefixOp(0xB2);
    ASSERT_REGISTERS(0, 0, 0, 0b00001000, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBB3", "[cpu_ops_res_b3_r8]")
{
    regs().e = 0b01011101;
    runCBPrefixOp(0xB3);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b00011101, 0, 0, 0, 0, 0, 2);

    regs().e = 0b00001000;
    runCBPrefixOp(0xB3);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b00001000, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBB4", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0b01011101;
    runCBPrefixOp(0xB4);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b00011101, 0, 0, 2);

    regs().h = 0b00001000;
    runCBPrefixOp(0xB4);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b00001000, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBB5", "[cpu_ops_res_b3_r8]")
{
    regs().l = 0b01011101;
    runCBPrefixOp(0xB5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b00011101, 0, 2);

    regs().l = 0b00001000;
    runCBPrefixOp(0xB5);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b00001000, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBB6", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b01011101;
    runCBPrefixOp(0xB6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b00011101);

    mem(0xABCD) = 0b00001000;
    runCBPrefixOp(0xB6);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b00001000);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBB7", "[cpu_ops_res_b3_r8]")
{
    regs().a = 0b01011101;
    runCBPrefixOp(0xB7);
    ASSERT_REGISTERS(0b00011101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().a = 0b00001000;
    runCBPrefixOp(0xB7);
    ASSERT_REGISTERS(0b00001000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBB8", "[cpu_ops_res_b3_r8]")
{
    regs().b = 0b11101110;
    runCBPrefixOp(0xB8);
    ASSERT_REGISTERS(0, 0b01101110, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().b = 0b01000100;
    runCBPrefixOp(0xB8);
    ASSERT_REGISTERS(0, 0b01000100, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBB9", "[cpu_ops_res_b3_r8]")
{
    regs().c = 0b11101110;
    runCBPrefixOp(0xB9);
    ASSERT_REGISTERS(0, 0, 0b01101110, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().c = 0b01000100;
    runCBPrefixOp(0xB9);
    ASSERT_REGISTERS(0, 0, 0b01000100, 0, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBBA", "[cpu_ops_res_b3_r8]")
{
    regs().d = 0b11101110;
    runCBPrefixOp(0xBA);
    ASSERT_REGISTERS(0, 0, 0, 0b01101110, 0, 0, 0, 0, 0, 0, 2);

    regs().d = 0b01000100;
    runCBPrefixOp(0xBA);
    ASSERT_REGISTERS(0, 0, 0, 0b01000100, 0, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBBB", "[cpu_ops_res_b3_r8]")
{
    regs().e = 0b11101110;
    runCBPrefixOp(0xBB);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01101110, 0, 0, 0, 0, 0, 2);

    regs().e = 0b01000100;
    runCBPrefixOp(0xBB);
    ASSERT_REGISTERS(0, 0, 0, 0, 0b01000100, 0, 0, 0, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBBC", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0b11101110;
    runCBPrefixOp(0xBC);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01101110, 0, 0, 2);

    regs().h = 0b01000100;
    runCBPrefixOp(0xBC);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0b01000100, 0, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBBD", "[cpu_ops_res_b3_r8]")
{
    regs().l = 0b11101110;
    runCBPrefixOp(0xBD);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01101110, 0, 2);

    regs().l = 0b01000100;
    runCBPrefixOp(0xBD);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0b01000100, 0, 4);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBBE", "[cpu_ops_res_b3_r8]")
{
    regs().h = 0xAB;
    regs().l = 0xCD;
    mem(0xABCD) = 0b11101110;
    runCBPrefixOp(0xBE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 2);
    REQUIRE(mem(0xABCD) == 0b01101110);

    mem(0xABCD) = 0b01000100;
    runCBPrefixOp(0xBE);
    ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0xAB, 0xCD, 0, 4);
    REQUIRE(mem(0xABCD) == 0b01000100);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0xCBBF", "[cpu_ops_res_b3_r8]")
{
    regs().a = 0b11101110;
    runCBPrefixOp(0xBF);
    ASSERT_REGISTERS(0b01101110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2);

    regs().a = 0b01000100;
    runCBPrefixOp(0xBF);
    ASSERT_REGISTERS(0b01000100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}