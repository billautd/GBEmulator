#include <CppUnitTest.h>
#include <Operations.h>
#include <Context.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(OperationsTests_ld_a_r16mem) {
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
};
