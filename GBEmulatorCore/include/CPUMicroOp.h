#pragma once

#include <Common.h>
#include <Registers.h>
#include <Interrupts.h>

enum CPUMicroOpType
{
    ADC_A_IMM8,
    ADD_A_IMM8,
    ADD_A_R8,
    ADD_R16_TO_HL,
    AND_A_IMM8,
    AND_A_R8,
    CALL_CONDITIONAL,
    CCF,
    CP_A_IMM8,
    CP_A_R8,
    CPL,
    DEC_R8,
    DEC_R16,
    DI,
    EI,
    FETCH_DECODE_SCHEDULE,
    FETCH_DECODE_SCHEDULE_CB_PREFIX,
    INC_R8,
    INC_R16,
    INTERNAL,
    JP_HL,
    JP_CONDITIONAL,
    JR,
    JR_CONDITIONAL,
    LD_R8_R8,
    OR_A_IMM8,
    OR_A_R8,
    PUSH_SP_HIGH_FROM_PC,
    PUSH_SP_LOW_FROM_PC,
    PUSH_SP_HIGH_FROM_R16STK,
    PUSH_SP_LOW_FROM_R16STK,
    READ_IMM8_HIGH,
    READ_IMM8_LOW,
    READ_SP_HIGH,
    READ_SP_LOW,
    READ_TGT3,
    READ_TMP_FROM_R8,
    RES_BIT,
    RET_CONDITIONAL,
    RLA,
    RLCA,
    RRA,
    RRCA,
    RR,
    SCF,
    SLA,
    SRL,
    SUB_A_IMM8,
    SWAP,
    TEST_BIT,
    WRITE_A_TO_TMP_ADDR,
    WRITE_A_TO_R16MEM_ADDR,
    WRITE_A_TO_LDH_ADDR,
    WRITE_INTERRUPT_TO_PC,
    WRITE_LDH_ADDR_TO_A,
    WRITE_R16MEM_ADDR_TO_A,
    WRITE_SP_LOW_TO_TMP_ADDR,
    WRITE_SP_HIGH_TO_TMP_ADDR,
    WRITE_TMP_ADDR_TO_A,
    WRITE_TMP_TO_PC,
    WRITE_TMP_TO_R8,
    WRITE_TMP_TO_R16,
    WRITE_TMP_TO_R16STK,
    XOR_A_IMM8,
    XOR_A_R8,
};

struct CPUMicroOpStruct
{
    CPUMicroOpType type;
    int cycles = 1;
    R8 r8_src = R8::A;
    R8 r8_dest = R8::A;
    R16 r16 = R16::BC;
    R16_MEM r16Mem = R16_MEM::BC;
    R16_STK r16Stk = R16_STK::BC;
    COND cond = COND::NZ;
    InterruptType intType = InterruptType::INT_VBLANK;
    u8 bit = 0;
    u8 tgt3 = 0;
};

class Context;
class CORE_API CPUMicroOp
{
private:
    Context &ctx;

    u8 tmp_low;
    u8 tmp_high;

public:
    CPUMicroOp(Context &ctx);
    ~CPUMicroOp();

    void logCPUMicroOp(const CPUMicroOpStruct &op, bool instructionDone);
    void runMicroOp(const CPUMicroOpStruct &op);
};