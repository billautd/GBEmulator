#include <CPUMicroOp.h>
#include <Context.h>

#define MICRO_OP_DEBUG false

CPUMicroOp::CPUMicroOp(Context &ctx) : ctx(ctx)
{
}

CPUMicroOp::~CPUMicroOp()
{
}

void CPUMicroOp::runMicroOp(const CPUMicroOpStruct &op)
{
#if MICRO_OP_DEBUG
    if (op.type == CPUMicroOpType::FETCH_DECODE_SCHEDULE)
        std::cout << std::endl;
    logCPUMicroOp(op, false);
#endif
    switch (op.type)
    {
    case CPUMicroOpType::ADC_A_IMM8:
    {
        u8 previousAValue = ctx.regs().a;
        u8 r8Value = tmp_low;
        bool carry = Common::getBit(ctx.regs().f, 4);
        u16 newValue16 = previousAValue + r8Value + carry;
        u8 newValue8 = (u8)newValue16;
        ctx.regs().a = newValue8;
        ctx.regs().setFlags(newValue8 == 0, 0, ((previousAValue & 0xF) + (r8Value & 0xF) + carry) > 0xF, newValue16 > 0xFF);
        break;
    }
    case CPUMicroOpType::ADD_A_IMM8:
    {
        u8 previousAValue = ctx.regs().a;
        u8 r8Value = tmp_low;
        u16 newValue16 = previousAValue + r8Value;
        u8 newValue8 = (u8)newValue16;
        ctx.regs().a = newValue8;
        ctx.regs().setFlags(newValue8 == 0, 0, ((previousAValue & 0xF) + (r8Value & 0xF)) > 0xF, newValue16 > 0xFF);
        break;
    }
    case CPUMicroOpType::ADD_A_R8:
    {
        u8 previousAValue = ctx.regs().a;
        u8 r8Value;
        if (op.r8_src == R8::HL)
            r8Value = tmp_low;
        else
            r8Value = ctx.regs().getFromR8(op.r8_src);
        u16 newValue16 = previousAValue + r8Value;
        u8 newValue8 = (u8)newValue16;
        ctx.regs().a = newValue8;
        ctx.regs().setFlags(newValue8 == 0, 0, ((previousAValue & 0xF) + (r8Value & 0xF)) > 0xF, newValue16 > 0xFF);
        break;
    }
    case CPUMicroOpType::ADD_R16_TO_HL:
    {
        u16 r16Val = ctx.regs().getFromR16(op.r16);
        u16 hlVal = ctx.regs().getFromR16(R16::HL);
        u32 newVal32 = r16Val + hlVal;
        u16 newVal16 = (u16)newVal32;
        ctx.regs().setRegFromR16(R16::HL, newVal16);
        ctx.regs().setFlags(-1, 0, ((hlVal & 0x0FFF) + (r16Val & 0x0FFF)) > 0x0FFF, newVal32 > 0xFFFF);
        break;
    }
    case CPUMicroOpType::AND_A_R8:
    {
        u8 r8Value;
        if (op.r8_src == R8::HL)
            r8Value = tmp_low;
        else
            r8Value = ctx.regs().getFromR8(op.r8_src);
        u8 newValue = ctx.regs().a & r8Value;
        ctx.regs().a = newValue;
        ctx.regs().setFlags(newValue == 0, 0, 1, 0);
        break;
    }
    case CPUMicroOpType::AND_A_IMM8:
    {
        u8 newValue = ctx.regs().a & tmp_low;
        ctx.regs().a = newValue;
        ctx.regs().setFlags(newValue == 0, 0, 1, 0);
        break;
    }
    case CPUMicroOpType::CALL_CONDITIONAL:
    {
        if (ctx.regs().checkCOND(op.cond))
        {
            ctx.cpu().pushToQueue({CPUMicroOpType::PUSH_SP_HIGH_FROM_PC}); // 4
            ctx.cpu().pushToQueue({CPUMicroOpType::PUSH_SP_LOW_FROM_PC});  // 4
            ctx.cpu().pushToQueue({CPUMicroOpType::WRITE_TMP_TO_PC});      // 4
        }
        break;
    }
    case CPUMicroOpType::CCF:
    {
        bool carry = Common::getBit(ctx.regs().f, 4);
        ctx.regs().setFlags(-1, 0, 0, !carry);
        break;
    }
    case CPUMicroOpType::CP_A_IMM8:
    {
        u8 r8Value = tmp_low;
        u8 a = ctx.regs().a;
        ctx.regs().setFlags((a - r8Value) == 0, 1, (a & 0xF) < (r8Value & 0xF), a < r8Value);
        break;
    }
    case CPUMicroOpType::CP_A_R8:
    {
        u8 r8Value;
        if (op.r8_src == R8::HL)
            r8Value = tmp_low;
        else
            r8Value = ctx.regs().getFromR8(op.r8_src);
        u8 a = ctx.regs().a;
        ctx.regs().setFlags((a - r8Value) == 0, 1, (a & 0xF) < (r8Value & 0xF), a < r8Value);
        break;
    }
    case CPUMicroOpType::CPL:
    {
        ctx.regs().a = ~ctx.regs().a;
        break;
    }
    case CPUMicroOpType::DEC_R8:
    {
        if (op.r8_dest == R8::HL)
        {
            u8 before = tmp_low;
            tmp_low--;
            ctx.regs().setFlags(tmp_low == 0, 1, (before & 0xF) == 0, -1);
        }
        else
        {
            u8 r8Value = ctx.regs().getFromR8(op.r8_dest);
            u8 newValue = r8Value - 1;
            ctx.regs().setRegFromR8(op.r8_dest, newValue);
            ctx.regs().setFlags(newValue == 0, 1, (r8Value & 0xF) == 0, -1);
        }
        break;
    }
    case CPUMicroOpType::DEC_R16:
    {
        u16 newValue = ctx.regs().getFromR16(op.r16) - 1;
        ctx.regs().setRegFromR16(op.r16, newValue);
        break;
    }
    case CPUMicroOpType::DI:
    {
        ctx.cpu().getInterrupts().setIME(false);
        break;
    }
    case CPUMicroOpType::EI:
    {
        ctx.cpu().getInterrupts().setEnablingIME(true);
        ctx.cpu().getInterrupts().setIMEDelay(1);
        break;
    }
    case CPUMicroOpType::FETCH_DECODE_SCHEDULE:
    {
        // Fetch opcode and increase PC
        ctx.cpu().setCurrentOpCode(ctx.mem().readMem(ctx.regs().pc++));
        // Then schedule operation
        ctx.cpu().runOp(ctx.cpu().opCode());
        break;
    }
    case CPUMicroOpType::FETCH_DECODE_SCHEDULE_CB_PREFIX:
    {
        // Fetch opcode and increase PC
        ctx.cpu().setCurrentCBPRefixOpCode(ctx.mem().readMem(ctx.regs().pc++));
        // Then schedule operation
        ctx.cpu().runOpCBPrefix(ctx.cpu().cbPrefixOpCode());
        break;
    }
    case CPUMicroOpType::INC_R8:
    {
        if (op.r8_dest == R8::HL)
        {
            u8 before = tmp_low;
            tmp_low++;
            ctx.regs().setFlags(tmp_low == 0, 0, (before & 0xF) == 0xF, -1);
        }
        else
        {
            u8 r8Value = ctx.regs().getFromR8(op.r8_dest);
            u8 newValue = r8Value + 1;
            ctx.regs().setRegFromR8(op.r8_dest, newValue);
            ctx.regs().setFlags(newValue == 0, 0, (r8Value & 0xF) == 0xF, -1);
        }
        break;
    }
    case CPUMicroOpType::INC_R16:
    {
        u16 newValue = ctx.regs().getFromR16(op.r16) + 1;
        ctx.regs().setRegFromR16(op.r16, newValue);
        break;
    }
    case CPUMicroOpType::INTERNAL:
    {
        break;
    }
    case CPUMicroOpType::JP_HL:
    {
        ctx.regs().pc = ctx.regs().getFromR16(R16::HL);
        break;
    }
    case CPUMicroOpType::JP_CONDITIONAL:
    {
        if (ctx.regs().checkCOND(op.cond))
        {
            ctx.regs().pc = (tmp_high << 8) + tmp_low;
            ctx.cpu().pushToQueue({CPUMicroOpType::INTERNAL});
        }
        break;
    }
    case CPUMicroOpType::JR:
    {
        // Value is signed, will jump after or before current PC
        ctx.regs().pc += (i8)tmp_low;
        break;
    }
    case CPUMicroOpType::JR_CONDITIONAL:
    {
        if (ctx.regs().checkCOND(op.cond))
            ctx.cpu().pushToQueue({CPUMicroOpType::JR}); // 4
        break;
    }
    case CPUMicroOpType::LD_R8_R8:
    {
        u8 newValue;
        // Source value
        if (op.r8_src == R8::HL)
            newValue = tmp_low;
        else
            newValue = ctx.regs().getFromR8(op.r8_src);
        // Dest value
        if (op.r8_dest == R8::HL)
            ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), tmp_low);
        else
            ctx.regs().setRegFromR8(op.r8_dest, newValue);
        break;
    }
    case CPUMicroOpType::OR_A_IMM8:
    {
        u8 newValue = ctx.regs().a | tmp_low;
        ctx.regs().a = newValue;
        ctx.regs().setFlags(newValue == 0, 0, 0, 0);
        break;
    }
    case CPUMicroOpType::OR_A_R8:
    {
        u8 r8Value;
        if (op.r8_src == R8::HL)
            r8Value = tmp_low;
        else
            r8Value = ctx.regs().getFromR8(op.r8_src);
        u8 newValue = ctx.regs().a | r8Value;
        ctx.regs().a = newValue;
        ctx.regs().setFlags(newValue == 0, 0, 0, 0);
        break;
    }
    case CPUMicroOpType::PUSH_SP_HIGH_FROM_PC:
    {
        u16 pc = ctx.regs().pc;
        ctx.regs().sp--;
        ctx.mem().writeMem(ctx.regs().sp, pc >> 8);
        break;
    }
    case CPUMicroOpType::PUSH_SP_LOW_FROM_PC:
    {
        u16 pc = ctx.regs().pc;
        ctx.regs().sp--;
        ctx.mem().writeMem(ctx.regs().sp, pc & 0XFF);
        break;
    }
    case CPUMicroOpType::PUSH_SP_HIGH_FROM_R16STK:
    {
        u16 r16StkValue = ctx.regs().getFromR16Stk(op.r16Stk);
        ctx.regs().sp--;
        ctx.mem().writeMem(ctx.regs().sp, r16StkValue >> 8);
        break;
    }
    case CPUMicroOpType::PUSH_SP_LOW_FROM_R16STK:
    {
        u16 r16StkValue = ctx.regs().getFromR16Stk(op.r16Stk);
        ctx.regs().sp--;
        ctx.mem().writeMem(ctx.regs().sp, r16StkValue & 0XFF);
        break;
    }
    case CPUMicroOpType::READ_IMM8_HIGH:
    {
        tmp_high = ctx.mem().readMem(ctx.regs().pc++);
        break;
    }
    case CPUMicroOpType::READ_IMM8_LOW:
    {
        tmp_low = ctx.mem().readMem(ctx.regs().pc++);
        break;
    }
    case CPUMicroOpType::READ_SP_HIGH:
    {
        tmp_high = ctx.mem().readMem(ctx.regs().sp++);
        break;
    }
    case CPUMicroOpType::READ_SP_LOW:
    {
        tmp_low = ctx.mem().readMem(ctx.regs().sp++);
        break;
    }
    case CPUMicroOpType::READ_TGT3:
    {
        u16 tgt3 = Registers::getTGT3FromCode(op.tgt3);
        tmp_high = tgt3 >> 8;
        tmp_low = tgt3 & 0xFF;
        break;
    }
    case CPUMicroOpType::READ_TMP_FROM_R8:
    {
        if (op.r8_src == R8::HL)
            tmp_low = ctx.mem().readMem(ctx.regs().getFromR16(R16::HL));
        else
            tmp_low = ctx.regs().getFromR8(op.r8_src);
        break;
    }
    case CPUMicroOpType::RES_BIT:
    {
        if (op.r8_dest == R8::HL)
            tmp_low = Common::resetBit(tmp_low, op.bit);
        else
        {
            u8 r8Value = ctx.regs().getFromR8(op.r8_dest);
            u8 newValue = Common::resetBit(r8Value, op.bit);
            ctx.regs().setRegFromR8(op.r8_dest, newValue);
        }
        break;
    }
    case CPUMicroOpType::RET_CONDITIONAL:
    {
        if (ctx.regs().checkCOND(op.cond))
        {
            ctx.cpu().pushToQueue({CPUMicroOpType::READ_SP_LOW});     // 4
            ctx.cpu().pushToQueue({CPUMicroOpType::READ_SP_HIGH});    // 4
            ctx.cpu().pushToQueue({CPUMicroOpType::WRITE_TMP_TO_PC}); // 4
        }
        ctx.cpu().pushToQueue({CPUMicroOpType::INTERNAL});
        break;
    }
    case CPUMicroOpType::RLA:
    {
        u8 r8Value = ctx.regs().a;
        bool b7 = Common::getBit(r8Value, 7);
        bool carry = Common::getBit(ctx.regs().f, 4);
        r8Value = (r8Value << 1 | carry);
        ctx.regs().a = r8Value;
        ctx.regs().setFlags(0, 0, 0, b7);
        break;
    }
    case CPUMicroOpType::RLCA:
    {
        u8 r8Value = ctx.regs().a;
        bool b7 = Common::getBit(r8Value, 7);
        r8Value = (r8Value << 1 | b7);
        ctx.regs().a = r8Value;
        ctx.regs().setFlags(0, 0, 0, b7);
        break;
    }
    case CPUMicroOpType::RR:
    {
        if (op.r8_dest == R8::HL)
        {
            bool b0 = Common::getBit(tmp_low, 0);
            bool carry = Common::getBit(ctx.regs().f, 4);
            tmp_low = (tmp_low >> 1) | (carry << 7);
            ctx.regs().setFlags(tmp_low == 0, 0, 0, b0);
        }
        else
        {
            u8 r8Value = ctx.regs().getFromR8(op.r8_dest);
            bool b0 = Common::getBit(r8Value, 0);
            bool carry = Common::getBit(ctx.regs().f, 4);
            u8 newValue = (r8Value >> 1) | (carry << 7);
            ctx.regs().setRegFromR8(op.r8_dest, newValue);
            ctx.regs().setFlags(newValue == 0, 0, 0, b0);
        }
        break;
    }
    case CPUMicroOpType::RRA:
    {
        u8 r8Value = ctx.regs().a;
        bool b0 = Common::getBit(r8Value, 0);
        bool carry = Common::getBit(ctx.regs().f, 4);
        r8Value = (r8Value >> 1 | (carry << 7));
        ctx.regs().a = r8Value;
        ctx.regs().setFlags(0, 0, 0, b0);
        break;
    }
    case CPUMicroOpType::RRCA:
    {
        u8 r8Value = ctx.regs().a;
        bool b0 = Common::getBit(r8Value, 0);
        r8Value = (r8Value >> 1 | (b0 << 7));
        ctx.regs().a = r8Value;
        ctx.regs().setFlags(0, 0, 0, b0);
        break;
    }
    case CPUMicroOpType::SCF:
    {
        ctx.regs().setFlags(-1, 0, 0, 1);
        break;
    }
    case CPUMicroOpType::SLA:
    {
        if (op.r8_dest == R8::HL)
        {
            bool carry = Common::getBit(tmp_low, 7);
            tmp_low = (tmp_low << 1);
            ctx.regs().setFlags(tmp_low == 0, 0, 0, carry);
        }
        else
        {
            u8 r8Value = ctx.regs().getFromR8(op.r8_dest);
            bool carry = Common::getBit(r8Value, 7);
            u8 newValue = (r8Value << 1);
            ctx.regs().setRegFromR8(op.r8_dest, newValue);
            ctx.regs().setFlags(newValue == 0, 0, 0, carry);
        }
        break;
    }
    case CPUMicroOpType::SRL:
    {
        if (op.r8_dest == R8::HL)
        {
            bool carry = Common::getBit(tmp_low, 0);
            tmp_low = (tmp_low >> 1);
            ctx.regs().setFlags(tmp_low == 0, 0, 0, carry);
        }
        else
        {
            u8 r8Value = ctx.regs().getFromR8(op.r8_dest);
            bool carry = Common::getBit(r8Value, 0);
            u8 newValue = (r8Value >> 1);
            ctx.regs().setRegFromR8(op.r8_dest, newValue);
            ctx.regs().setFlags(newValue == 0, 0, 0, carry);
        }
        break;
    }
    case CPUMicroOpType::SUB_A_IMM8:
    {
        u8 previousAValue = ctx.regs().a;
        u8 r8Value = tmp_low;
        u8 newValue8 = previousAValue - r8Value;
        ctx.regs().a = newValue8;
        ctx.regs().setFlags(newValue8 == 0, 1, ((int)(previousAValue & 0xF) - (int)(r8Value & 0xF)) < 0, ((int)previousAValue - (int)r8Value) < 0);
        break;
    }
    case CPUMicroOpType::SWAP:
    {
        if (op.r8_dest == R8::HL)
        {
            tmp_low = ((tmp_low & 0xF) << 4) + ((tmp_low & 0xF0) >> 4);
            ctx.regs().setFlags(tmp_low == 0, 0, 0, 0);
        }
        else
        {
            u8 r8Value = ctx.regs().getFromR8(op.r8_dest);
            u8 newValue = ((r8Value & 0xF) << 4) + ((r8Value & 0xF0) >> 4);
            ctx.regs().setRegFromR8(op.r8_dest, newValue);
            ctx.regs().setFlags(newValue == 0, 0, 0, 0);
        }
        break;
    }
    case CPUMicroOpType::TEST_BIT:
    {
        u8 r8Value;
        if (op.r8_src == R8::HL)
            r8Value = tmp_low;
        else
            r8Value = ctx.regs().getFromR8(op.r8_src);

        bool isBitSet = Common::getBit(r8Value, op.bit);
        ctx.regs().setFlags(!isBitSet, 0, 1, -1);
        break;
    }
    case CPUMicroOpType::WRITE_A_TO_LDH_ADDR:
    {
        u16 address = 0xFF00 | tmp_low;
        ctx.mem().writeMem(address, ctx.regs().a);
        break;
    }
    case CPUMicroOpType::WRITE_A_TO_R16MEM_ADDR:
    {
        ctx.mem().writeMem(ctx.regs().getPointerFromR16Mem(op.r16Mem), ctx.regs().a);
        ctx.regs().updateHLMem(op.r16Mem);
        break;
    }
    case CPUMicroOpType::WRITE_A_TO_TMP_ADDR:
    {
        u16 address = (tmp_high << 8) | tmp_low;
        ctx.mem().writeMem(address, ctx.regs().a);
        break;
    }
    case CPUMicroOpType::WRITE_INTERRUPT_TO_PC:
    {
        ctx.regs().pc = Interrupts::getAddressFromType(op.intType);
        break;
    }
    case CPUMicroOpType::WRITE_LDH_ADDR_TO_A:
    {
        u16 address = 0xFF00 | tmp_low;
        ctx.regs().a = ctx.mem().readMem(address);
        break;
    }
    case CPUMicroOpType::WRITE_R16MEM_ADDR_TO_A:
    {
        ctx.regs().a = ctx.mem().readMem(ctx.regs().getPointerFromR16Mem(op.r16Mem));
        ctx.regs().updateHLMem(op.r16Mem);
        break;
    }
    case CPUMicroOpType::WRITE_SP_LOW_TO_TMP_ADDR:
    {
        u16 address = (tmp_high << 8) | tmp_low;
        ctx.mem().writeMem(address, ctx.regs().sp & 0xFF);
        break;
    }
    case CPUMicroOpType::WRITE_SP_HIGH_TO_TMP_ADDR:
    {
        u16 address = (tmp_high << 8) | tmp_low;
        address++;
        ctx.mem().writeMem(address, ctx.regs().sp >> 8);
        break;
    }
    case CPUMicroOpType::WRITE_TMP_ADDR_TO_A:
    {
        u16 address = (tmp_high << 8) | tmp_low;
        ctx.regs().a = ctx.mem().readMem(address);
        break;
    }
    case CPUMicroOpType::WRITE_TMP_TO_PC:
    {
        u16 newValue = (tmp_high << 8) | tmp_low;
        ctx.regs().pc = newValue;
        break;
    }
    case CPUMicroOpType::WRITE_TMP_TO_R8:
    {
        if (op.r8_dest == R8::HL)
            ctx.mem().writeMem(ctx.regs().getFromR16(R16::HL), tmp_low);
        else
            ctx.regs().setRegFromR8(op.r8_dest, tmp_low);
        break;
    }
    case CPUMicroOpType::WRITE_TMP_TO_R16:
    {
        u16 newValue = (tmp_high << 8) | tmp_low;
        ctx.regs().setRegFromR16(op.r16, newValue);
        break;
    }
    case CPUMicroOpType::WRITE_TMP_TO_R16STK:
    {
        u16 newValue = (tmp_high << 8) | tmp_low;
        ctx.regs().setRegFromR16Stk(op.r16Stk, newValue);
        break;
    }
    case CPUMicroOpType::XOR_A_IMM8:
    {
        u8 r8Value = tmp_low;
        u8 newValue = ctx.regs().a ^ r8Value;
        ctx.regs().a = newValue;
        ctx.regs().setFlags(newValue == 0, 0, 0, 0);
        break;
    }
    case CPUMicroOpType::XOR_A_R8:
    {
        u8 r8Value;
        if (op.r8_src == R8::HL)
            r8Value = tmp_low;
        else
            r8Value = ctx.regs().getFromR8(op.r8_src);
        u8 newValue = ctx.regs().a ^ r8Value;
        ctx.regs().a = newValue;
        ctx.regs().setFlags(newValue == 0, 0, 0, 0);
        break;
    }
    }
}

void CPUMicroOp::logCPUMicroOp(const CPUMicroOpStruct &op, bool instructionDone)
{
    std::cout << std::format("{} micro op [Type {}], [Cycles {}], [R8 SRC {}], [R8 DEST {}], [R16 {}], [R16 MEM {}], [R16 STK {}], [COND {}], [bit {}], [tgt3 {}]\n",
                             instructionDone ? "After" : "Before",
                             (int)op.type, op.cycles, R8_STR[(int)op.r8_src], R8_STR[(int)op.r8_dest], R16_STR[(int)op.r16], R16_MEM_STR[(int)op.r16Mem], R16_STK_STR[(int)op.r16Stk],
                             COND_STR[(int)op.cond], op.bit, op.tgt3);
    std::cout << ctx.regs().log() << std::endl;
}