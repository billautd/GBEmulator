#include "CppUnitTest.h"
#include "../../GBEmulator/GLEmulatorCore/include/Context.h"
#include "../../GBEmulator/GLEmulatorCore/include/Operations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(OperationsTests) {
public:
	Context* ctx() { return Context::get();	}
	Registers& regs() { return ctx()->getRegisters(); }

	TEST_METHOD_INITIALIZE(Init) {
		Context* ctx = Context::get();
		ctx->getRegisters().a = 0x00;
		ctx->getRegisters().b = 0x00;
		ctx->getRegisters().c = 0x00;
		ctx->getRegisters().d = 0x00;
		ctx->getRegisters().e = 0x00;
		ctx->getRegisters().f = 0x00;
		ctx->getRegisters().g = 0x00;
		ctx->getRegisters().h = 0x00;
		ctx->getRegisters().l = 0x00;
		ctx->getRegisters().sp = 0x0000;
		ctx->getRegisters().pc = 0x0000;
	}
	TEST_METHOD(OperationsTests_nop) {
		Logger::WriteMessage("OperationsTests_nop");
		Operations::nop();
		Logger::WriteMessage("OperationsTests_nop -> Check registers not changed");
		Assert::AreEqual((u8)0x00, regs().a);
		Assert::AreEqual((u8)0x00, regs().b);
		Assert::AreEqual((u8)0x00, regs().c);
		Assert::AreEqual((u8)0x00, regs().d);
		Assert::AreEqual((u8)0x00, regs().e);
		Assert::AreEqual((u8)0x00, regs().f);
		Assert::AreEqual((u8)0x00, regs().g);
		Assert::AreEqual((u8)0x00, regs().h);
		Assert::AreEqual((u8)0x00, regs().l);
		Assert::AreEqual((u16)0x0000, regs().sp);
		Logger::WriteMessage("OperationsTests_nop -> Check PC incremented by 1");
		Assert::AreEqual((u16)0x0001, regs().pc);
	}
};
