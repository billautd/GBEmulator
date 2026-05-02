#pragma once

#include <Common.h>

enum InterruptType
{
    INT_VBLANK,
    INT_LCD,
    INT_TIMER,
    INT_SERIAL,
    INT_JOYPAD
};

class Context;
class CORE_API Interrupts
{
private:
    Context &ctx;
    bool ime = false;
    bool enablingIME = false;
    int imeDelay = 0;

public:
    const static u16 IF = 0xFF0F;
    const static u16 IE = 0xFFFF;

    Interrupts(Context &ctx);
    ~Interrupts();

    void handle();

    bool isIME() { return ime; }
    void setIME(bool ime) { this->ime = ime; }

    void updateIME();
    bool isIMEJustEnabled() { return ime; }
    bool isEnablingIME() { return enablingIME; }
    void setEnablingIME(bool enablingIME) { this->enablingIME = enablingIME; }
    void setIMEDelay(int delay) { imeDelay = delay; }

    static u16 getAddressFromType(InterruptType type);

    bool checkInterrupts();
    bool checkInterrupt(InterruptType type);

    void requestInterrupt(InterruptType type);
    void resetInterrupt(InterruptType type);
};