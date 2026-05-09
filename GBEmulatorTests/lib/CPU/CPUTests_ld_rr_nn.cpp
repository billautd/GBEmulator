#include <CPUTestsFixture.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x01", "[cpu_ops_ld_rr_nn]")
{
	mem(0x01) = 0xAB;
	mem(0x02) = 0xCD;
	runOp(0x01);

	ASSERT_REGISTERS(0, 0xCD, 0xAB, 0, 0, 0, 0, 0, 0, 3);
	REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x11", "[cpu_ops_ld_rr_nn]")
{
	mem(0x01) = 0xAB;
	mem(0x02) = 0xCD;
	runOp(0x11);

	ASSERT_REGISTERS(0, 0, 0, 0xCD, 0xAB, 0, 0, 0, 0, 3);
	REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x21", "[cpu_ops_ld_rr_nn]")
{
	mem(0x01) = 0xAB;
	mem(0x02) = 0xCD;
	runOp(0x21);

	ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0xCD, 0xAB, 0, 3);
	REQUIRE(ticks() == 12);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_0x31", "[cpu_ops_ld_rr_nn]")
{
	mem(0x01) = 0xAB;
	mem(0x02) = 0xCD;
	runOp(0x31);

	ASSERT_REGISTERS(0, 0, 0, 0, 0, 0, 0, 0, 0xCDAB, 3);
	REQUIRE(ticks() == 12);
}