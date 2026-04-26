#include <catch2/catch_test_macros.hpp>
#include <CPUTestsFixture.h>
#include <CPU.h>
#include <Context.h>
#include <Common.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_method_calls", "[cpu]")
{
	for (int i = 0; i < 256; i++)
	{
		std::cout << std::format("Code : {}\n", Common::toHexStr((u8)i));
		// Invalid op codes
		if (i == 0xD3 || i == 0xDB || i == 0xDD || i == 0xE3 || i == 0xE4 || i == 0xEB || i == 0xEC || i == 0xED || i == 0xF4 || i == 0xFC || i == 0xFD)
		{
			REQUIRE_THROWS_AS(runOp((u8)i), std::runtime_error);
		}
		// Valid op codes
		else
		{
			REQUIRE_NOTHROW(runOp((u8)i));
		}
	}
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_cb_prefix_method_calls", "[cpu]")
{
	for (int i = 0; i < 256; i++)
	{
		std::cout << std::format("CB Code : {}\n", Common::toHexStr((u8)i));
		mem(regs().pc + 1) = (u8)i;
		REQUIRE_NOTHROW(runOp(0xCB));
	}
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_popFromStack", "[cpu]")
{
	regs().sp = 0xCFFD;
	mem(0xCFFD) = 0xAB;
	mem(0xCFFE) = 0xCD;

	REQUIRE(cpu().popFromStack() == 0xCDAB);
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_pushToStack", "[cpu]")
{
	regs().sp = 0xCFFF;
	cpu().pushToStack(0xABCD);

	REQUIRE(regs().sp == 0xCFFD);
	REQUIRE(mem(0xCFFE) == 0xAB);
	REQUIRE(mem(0xCFFD) == 0xCD);
}