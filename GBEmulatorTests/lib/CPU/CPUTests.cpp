#include <CPUTestsFixture.h>
#include <Common.h>

TEST_CASE_METHOD(CPUTestsFixture, "cpu_method_calls", "[cpu]")
{
	for (int i = 0; i < 256; i++)
	{
		regs().pc = 0;
		cpu().clearQueue();
		cpu().setCycles(0);
		cpu().setCurrentTCycles(0);
		cpu().setHalted(false);
		if (i == 0xCB)
			continue;
		// Invalid op codes
		if (i == 0xD3 || i == 0xDB || i == 0xDD || i == 0xE3 || i == 0xE4 || i == 0xEB || i == 0xEC || i == 0xED || i == 0xF4 || i == 0xFC || i == 0xFD)
			REQUIRE_THROWS_AS(runOp((u8)i), std::runtime_error);
		// Valid op codes
		else
			REQUIRE_NOTHROW(runOp((u8)i));
	}
}

TEST_CASE_METHOD(CPUTestsFixture, "cpu_cb_prefix_method_calls", "[cpu]")
{
	for (int i = 0; i < 256; i++)
	{
		regs().pc = 0;
		cpu().clearQueue();
		cpu().setCycles(0);
		cpu().setCurrentTCycles(0);
		REQUIRE_NOTHROW(runCBPrefixOp((u8)i));
	}
}