#include <CppUnitTest.h>
#include <Operations.h>
#include <Context.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(OperationsTests_ld_r16_imm16) {
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

	BEGIN_TEST_METHOD_ATTRIBUTE(OperationsTests_ld_bc_imm16_0x01)
		TEST_DESCRIPTION("Test on LD BC,d16 instruction for code 0x01")
	END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(OperationsTests_ld_bc_imm16_0x01) {
		Registers& regs = Context::get()->getRegisters();

		Context::get()->setCurrentOpCode(0x01);
		Context::get()->getMemory().at(0x01) = 0xAB;
		Context::get()->getMemory().at(0x02) = 0xCD;

		Operations::ld_r16_imm16();
		//Check registers not changed;
		Assert::AreEqual((u8)0x00, regs.a);
		Assert::AreEqual((u8)0x00, regs.d);
		Assert::AreEqual((u8)0x00, regs.e);
		Assert::AreEqual((u8)0x00, regs.f);
		Assert::AreEqual((u8)0x00, regs.g);
		Assert::AreEqual((u8)0x00, regs.h);
		Assert::AreEqual((u8)0x00, regs.l);
		Assert::AreEqual((u16)0x0000, regs.sp);
		//Check registers changed;
		Assert::AreEqual((u8)0xCD, regs.b);
		Assert::AreEqual((u8)0xAB, regs.c);
		//Check PC incremented by 3;
		Assert::AreEqual((u16)0x0003, regs.pc);
	}
};
