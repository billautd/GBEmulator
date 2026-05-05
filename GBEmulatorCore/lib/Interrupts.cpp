#include <Interrupts.h>
#include <Context.h>

#define INTERRUPTS_DEBUG true

Interrupts::Interrupts(Context &ctx) : ctx(ctx)
{
}

Interrupts::~Interrupts()
{
}

void Interrupts::handle()
{
    if (imeDelay == 0 && isEnablingIME())
    {
        setIME(true);
        setEnablingIME(false);
    }
    if (isIME())
    {
        checkInterrupts();
    }
    if (imeDelay > 0)
        imeDelay--;
}

bool Interrupts::checkInterrupts()
{
    if (checkInterrupt(InterruptType::INT_VBLANK))
    {
#if INTERRUPTS_DEBUG
        //std::cout << "Detected VBLANK interrupt" << std::endl;
#endif
        processInterrupt(InterruptType::INT_VBLANK);
        return true;
    }
    else if (checkInterrupt(InterruptType::INT_LCD))
    {
#if INTERRUPTS_DEBUG
        std::cout << "Detected LCD interrupt PC " << ctx.regs().pc << std::endl;
#endif
        //processInterrupt(InterruptType::INT_LCD);
        return true;
    }
    else if (checkInterrupt(InterruptType::INT_TIMER))
    {
#if INTERRUPTS_DEBUG
        std::cout << "Detected TIMER interrupt" << std::endl;
#endif
        //processInterrupt(InterruptType::INT_TIMER);
        return true;
    }
    else if (checkInterrupt(InterruptType::INT_SERIAL))
    {
#if INTERRUPTS_DEBUG
        std::cout << "Detected SERIAL interrupt" << std::endl;
#endif
        //processInterrupt(InterruptType::INT_SERIAL);
        return true;
    }
    else if (checkInterrupt(InterruptType::INT_JOYPAD))
    {
#if INTERRUPTS_DEBUG
        std::cout << "Detected JOYPAD interrupt" << std::endl;
#endif
        //processInterrupt(InterruptType::INT_JOYPAD);
        return true;
    }
    return false;
}

bool Interrupts::checkInterrupt(InterruptType type)
{
    if (!isIME())
        return false;
    bool isIE = ctx.mem().readMem(IE) & (0b1 << type);
    bool isIF = ctx.mem().readMem(IF) & (0b1 << type);
    return isIE && isIF;
}

void Interrupts::processInterrupt(InterruptType type)
{
    resetInterrupt(type);
    ctx.cpu().pushToQueue({CPUMicroOpType::INTERNAL});             // 4
    ctx.cpu().pushToQueue({CPUMicroOpType::INTERNAL});             // 4
    ctx.cpu().pushToQueue({CPUMicroOpType::PUSH_SP_HIGH_FROM_PC}); // 4
    ctx.cpu().pushToQueue({CPUMicroOpType::PUSH_SP_LOW_FROM_PC});  // 4
    ctx.cpu().pushToQueue({
        .type = CPUMicroOpType::WRITE_INTERRUPT_TO_PC,
        .intType = type,
    }); // 4
    setIME(false);
}

void Interrupts::requestInterrupt(InterruptType type)
{
    u8 ifValue = ctx.mem().readMem(IF);
    u8 newValue = ctx.mem().readMem(IF) | (0b1 << type);
    ctx.mem().writeMem(IF, newValue);
}

void Interrupts::resetInterrupt(InterruptType type)
{
    u8 ifValue = ctx.mem().readMem(IF);
    u8 newValue = ifValue & (0xFF - (u8)pow(2, (int)type));
    ctx.mem().writeMem(IF, newValue);
}

u16 Interrupts::getAddressFromType(InterruptType type)
{
    switch (type)
    {
    case InterruptType::INT_JOYPAD:
        return 0x60;
    case InterruptType::INT_LCD:
        return 0x48;
    case InterruptType::INT_SERIAL:
        return 0x58;
    case InterruptType::INT_TIMER:
        return 0x50;
    case InterruptType::INT_VBLANK:
        return 0x40;
    }
    throw std::invalid_argument(std::string("Interrupts::getAddressFromType -> Invalid type " + type));
}