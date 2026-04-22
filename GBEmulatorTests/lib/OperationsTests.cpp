#include <CppUnitTest.h>
#include <Operations.h>
#include <Context.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(OperationsTests) {
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

	TEST_METHOD(OperationTests_MethodCalls) {
		for (int i = 0; i < 256; i++) {
			//Invalid op codes
			if (i == 0xD3 || i == 0xDB || i == 0xDD || i == 0xE3
				|| i == 0xE4 || i == 0xEB || i == 0xEC || i == 0xED
				|| i == 0xF4 || i == 0xFC || i == 0xFD) {
				Assert::ExpectException<std::runtime_error>([&]() { Operations::runOp((u8)i); });
			}
			//Valid op codes
			else {
			try {
				Operations::runOp((u8)i);
			}
			catch (...){
				std::wstringstream msg;
				msg << L"Operation not managed : " << i;
				Assert::Fail(msg.str().c_str());
			}
			}
		}
	}
};
