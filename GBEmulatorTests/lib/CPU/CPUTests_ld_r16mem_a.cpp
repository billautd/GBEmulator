#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x02", "[cpu_ops_ld_r16mem_a]")
{
	// Value to copy
	regs().a = 0xEF;
	// Byte pointed to
	regs().b = 0xAB;
	regs().c = 0xCD;

	runOp(0x02);

	ASSERT_REGISTERS(0xEF, 0xAB, 0xCD, 0, 0, 0, 0, 0, 0, 0, 1);
	REQUIRE(mem(0xABCD) == 0xEF);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x12", "[cpu_ops_ld_r16mem_a]")
{
	// Value to copy
	regs().a = 0xEF;
	// Byte pointed to
	regs().d = 0xAB;
	regs().e = 0xCD;

	runOp(0x12);

	ASSERT_REGISTERS(0xEF, 0, 0, 0xAB, 0xCD, 0, 0, 0, 0, 0, 1);
	REQUIRE(mem(0xABCD) == 0xEF);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x22", "[cpu_ops_ld_r16mem_a]")
{
	// Value to copy
	regs().a = 0xEF;
	// Byte pointed to
	regs().h = 0xAB;
	regs().l = 0xCD;

	runOp(0x22);

	ASSERT_REGISTERS(0xEF, 0, 0, 0, 0, 0, 0, 0xAB, 0xCE, 0, 1);
	REQUIRE(mem(0xABCD) == 0xEF);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x32", "[cpu_ops_ld_r16mem_a]")
{
	// Value to copy
	regs().a = 0xEF;
	// Byte pointed to
	regs().h = 0xAB;
	regs().l = 0xCD;

	runOp(0x32);

	ASSERT_REGISTERS(0xEF, 0, 0, 0, 0, 0, 0, 0xAB, 0xCC, 0, 1);
	REQUIRE(mem(0xABCD) == 0xEF);
}