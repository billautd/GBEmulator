#include <CppUnitTest.h>
#include <Context.h>
#include <Registers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(RegistersTests) {
private:
	Registers regs;
public:
	TEST_METHOD_INITIALIZE(Init) {
		Logger::WriteMessage("RegistersTests::Init");
		regs = Registers();

		Context::get()->initMemory();
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(RegistersTest_getR8FromCode)
		TEST_DESCRIPTION("Test on method getR8FromCode")
	END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(RegistersTest_getR8FromCode) {
		//Check correct R8 is returned
		Assert::AreEqual((int)R8::B , (int)Registers::getR8FromCode(0));
		Assert::AreEqual((int)R8::C , (int)Registers::getR8FromCode(1));
		Assert::AreEqual((int)R8::D , (int)Registers::getR8FromCode(2));
		Assert::AreEqual((int)R8::E , (int)Registers::getR8FromCode(3));
		Assert::AreEqual((int)R8::H , (int)Registers::getR8FromCode(4));
		Assert::AreEqual((int)R8::L , (int)Registers::getR8FromCode(5));
		Assert::AreEqual((int)R8::HL, (int)Registers::getR8FromCode(6));
		Assert::AreEqual((int)R8::A , (int)Registers::getR8FromCode(7));
		//Check assertion raised if wrong value
		Assert::ExpectException<std::invalid_argument>([]() { Registers::getR8FromCode(8); });
		Assert::ExpectException<std::invalid_argument>([]() { Registers::getR8FromCode(-1); });
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(RegistersTest_setRegFromR8)
		TEST_DESCRIPTION("Test on method setRegFromR8")
	END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(RegistersTest_setRegFromR8) {
		//Set all registers through method
		regs.setRegFromR8(R8::B, 0x01);
		regs.setRegFromR8(R8::C, 0x02);
		regs.setRegFromR8(R8::D, 0x03);
		regs.setRegFromR8(R8::E, 0x04);
		regs.setRegFromR8(R8::H, 0x05);
		regs.setRegFromR8(R8::L, 0x06);
		//regs.setRegFromR8(R8::HL, 0x07);
		regs.setRegFromR8(R8::A, 0x08);

		//Asserts updated registers
		Assert::AreEqual((u8)0x01, regs.b);
		Assert::AreEqual((u8)0x02, regs.c);
		Assert::AreEqual((u8)0x03, regs.d);
		Assert::AreEqual((u8)0x04, regs.e);
		Assert::AreEqual((u8)0x05, regs.h);
		Assert::AreEqual((u8)0x06, regs.l);
		//Assert::AreEqual((u8)0x07, regs.hl);
		Assert::AreEqual((u8)0x08, regs.a);
	}


	BEGIN_TEST_METHOD_ATTRIBUTE(RegistersTest_getFromR8)
		TEST_DESCRIPTION("Test on method getFromR8")
	END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(RegistersTest_getFromR8) {
		//Sets registers directly
		regs.b = 0x01;
		regs.c = 0x02;
		regs.d = 0x03;
		regs.e = 0x04;
		regs.h = 0x05;
		regs.l = 0x06;
		//regs.hl = 0x07;
		regs.a = 0x08;

		//Asserts correct values returned
		Assert::AreEqual((u8)0x01, regs.getFromR8(R8::B));
		Assert::AreEqual((u8)0x02, regs.getFromR8(R8::C));
		Assert::AreEqual((u8)0x03, regs.getFromR8(R8::D));
		Assert::AreEqual((u8)0x04, regs.getFromR8(R8::E));
		Assert::AreEqual((u8)0x05, regs.getFromR8(R8::H));
		Assert::AreEqual((u8)0x06, regs.getFromR8(R8::L));
		//Assert::AreEqual((u8)0x07, regs.hl);
		Assert::AreEqual((u8)0x08, regs.getFromR8(R8::A));
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(RegistersTest_getR16FromCode)
		TEST_DESCRIPTION("Test on method getR16FromCode")
	END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(RegistersTest_getR16FromCode) {
		Assert::AreEqual((int)R16::BC, (int)Registers::getR16FromCode(0));
		Assert::AreEqual((int)R16::DE, (int)Registers::getR16FromCode(1));
		Assert::AreEqual((int)R16::HL, (int)Registers::getR16FromCode(2));
		Assert::AreEqual((int)R16::SP, (int)Registers::getR16FromCode(3));
		Assert::ExpectException<std::invalid_argument>([]() { Registers::getR16FromCode(4); });
		Assert::ExpectException<std::invalid_argument>([]() { Registers::getR16FromCode(8); });
		Assert::ExpectException<std::invalid_argument>([]() { Registers::getR16FromCode(-1); });
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(RegistersTest_setRegFromR16)
		TEST_DESCRIPTION("Test on method setRegFromR16")
	END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(RegistersTest_setRegFromR16) {
		//Set all registers through method
		regs.setRegFromR16(R16::BC, 0x0102);
		regs.setRegFromR16(R16::DE, 0x0304);
		regs.setRegFromR16(R16::HL, 0x0506);
		regs.setRegFromR16(R16::SP, 0x0708);

		//Asserts updated registers
		Assert::AreEqual((u8)0x01, regs.b);
		Assert::AreEqual((u8)0x02, regs.c);
		Assert::AreEqual((u8)0x03, regs.d);
		Assert::AreEqual((u8)0x04, regs.e);
		Assert::AreEqual((u8)0x05, regs.h);
		Assert::AreEqual((u8)0x06, regs.l);
		Assert::AreEqual((u16)0x0708, regs.sp);
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(RegistersTest_getR16MemFromCode)
		TEST_DESCRIPTION("Test on method getR16MemFromCode")
	END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(RegistersTest_getR16MemFromCode) {
		Assert::AreEqual((int)R16_MEM::BC, (int)Registers::getR16MemFromCode(0));
		Assert::AreEqual((int)R16_MEM::DE, (int)Registers::getR16MemFromCode(1));
		Assert::AreEqual((int)R16_MEM::HLI, (int)Registers::getR16MemFromCode(2));
		Assert::AreEqual((int)R16_MEM::HLD, (int)Registers::getR16MemFromCode(3));
		Assert::ExpectException<std::invalid_argument>([]() { Registers::getR16MemFromCode(4); });
		Assert::ExpectException<std::invalid_argument>([]() { Registers::getR16MemFromCode(8); });
		Assert::ExpectException<std::invalid_argument>([]() { Registers::getR16MemFromCode(-1); });
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(RegistersTest_getPointerFromR16Mem)
		TEST_DESCRIPTION("Test on method getPointerFromR16Mem")
	END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(RegistersTest_getPointerFromR16Mem) {
		//Sets registers directly
		regs.b = 0x01;
		regs.c = 0x02;
		regs.d = 0x03;
		regs.e = 0x04;
		regs.h = 0x05;
		regs.l = 0x06;
		//regs.hl = 0x07;
		regs.a = 0x08;

		//Asserts correct values returned
		Assert::AreEqual((u16)0x0102, regs.getPointerFromR16Mem(R16_MEM::BC));
		Assert::AreEqual((u16)0x0304, regs.getPointerFromR16Mem(R16_MEM::DE));
		Assert::AreEqual((u16)0x0506, regs.getPointerFromR16Mem(R16_MEM::HLI));
		Assert::AreEqual((u16)0x0506, regs.getPointerFromR16Mem(R16_MEM::HLD));
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(RegistersTest_imm8)
		TEST_DESCRIPTION("Test on method imm8")
	END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(RegistersTest_imm8) {
		regs.pc = 0x1020;

		Context::get()->getMemory().at(0x1020) = 0x01;
		Context::get()->getMemory().at(0x1021) = 0x02;
		Context::get()->getMemory().at(0x1022) = 0x03;
		Context::get()->getMemory().at(0x1023) = 0x04;

		Assert::AreEqual((u8)0x02, regs.imm8());
		regs.pc++;
		Assert::AreEqual((u8)0x03, regs.imm8());
		regs.pc++;
		Assert::AreEqual((u8)0x04, regs.imm8());
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(RegistersTest_imm16)
		TEST_DESCRIPTION("Test on method imm16")
	END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(RegistersTest_imm16) {
		regs.pc = 0x1020;

		Context::get()->getMemory().at(0x1020) = 0x01;
		Context::get()->getMemory().at(0x1021) = 0x02;
		Context::get()->getMemory().at(0x1022) = 0x03;
		Context::get()->getMemory().at(0x1023) = 0x04;

		Assert::AreEqual((u16)0x0302, regs.imm16());
		regs.pc++;
		Assert::AreEqual((u16)0x0403, regs.imm16());
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(RegistersTest_updateHLMem)
		TEST_DESCRIPTION("Test on method updateHLMem")
	END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(RegistersTest_updateHLMem) {
		regs.h = 0x01;
		regs.l = 0x02;

		//Checks increment
		regs.updateHLMem(R16_MEM::HLI);
		Assert::AreEqual((u8)0x01, regs.h);
		Assert::AreEqual((u8)0x03, regs.l);

		//Checks decrement
		regs.updateHLMem(R16_MEM::HLD);
		Assert::AreEqual((u8)0x01, regs.h);
		Assert::AreEqual((u8)0x02, regs.l);

		//Checks unchanged
		regs.updateHLMem(R16_MEM::BC);
		Assert::AreEqual((u8)0x01, regs.h);
		Assert::AreEqual((u8)0x02, regs.l);

		regs.updateHLMem(R16_MEM::DE);
		Assert::AreEqual((u8)0x01, regs.h);
		Assert::AreEqual((u8)0x02, regs.l);
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(RegistersTest_setFlags)
		TEST_DESCRIPTION("Test on method setFlags")
		END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(RegistersTest_setFlags) {
		regs.f = 0x0000;
		regs.setFlags(1, 1, 1, 1);
		Assert::AreEqual((u8)0b11110000, regs.f);

		regs.setFlags(1, 0, 1, 0);
		Assert::AreEqual((u8)0b10100000, regs.f);

		regs.setFlags(-1, -1, -1, -1);
		Assert::AreEqual((u8)0b10100000, regs.f);

		regs.setFlags(0, 0, 0, 0);
		Assert::AreEqual((u8)0b00000000, regs.f);
	}
};
