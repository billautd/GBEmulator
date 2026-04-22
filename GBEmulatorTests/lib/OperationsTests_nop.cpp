#include <CppUnitTest.h>
#include <Operations.h>
#include <Context.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(OperationsTests_nop) {
public:
	TEST_METHOD_INITIALIZE(Init) {
		Context* ctx = Context::get();
		ctx->initMemory();
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

	BEGIN_TEST_METHOD_ATTRIBUTE(OperationsTests_nop_0x00)
		TEST_DESCRIPTION("Test on nop instruction for code 0x00")
	END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(OperationsTests_nop_0x00) {
		Registers& regs = Context::get()->getRegisters();

		Context::get()->setCurrentOpCode(0x00);

		Operations::nop();
		//Check registers not changed
		Assert::AreEqual((u8)0x00, regs.a);
		Assert::AreEqual((u8)0x00, regs.b);
		Assert::AreEqual((u8)0x00, regs.c);
		Assert::AreEqual((u8)0x00, regs.d);
		Assert::AreEqual((u8)0x00, regs.e);
		Assert::AreEqual((u8)0x00, regs.f);
		Assert::AreEqual((u8)0x00, regs.g);
		Assert::AreEqual((u8)0x00, regs.h);
		Assert::AreEqual((u8)0x00, regs.l);
		Assert::AreEqual((u16)0x0000, regs.sp);
		//Check PC incremented by 1
		Assert::AreEqual((u16)0x0001, regs.pc);
	}
};
