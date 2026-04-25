#include <Registers.h>
#include <Context.h>

class CPUTestsFixture
{
private:
    static int id;

protected:
    Context *ctx;
    int getID()
    {
        return ++id;
    }

public:
    CPUTestsFixture() : ctx(new Context())
    {
        ctx->regs().pc = 0;
    }

    // Shortcut getters
    Registers &regs() { return ctx->regs(); }
    CPU &cpu() { return ctx->cpu(); }
    std::vector<u8> &mem() { return ctx->mem(); }
    void runOp(u8 code) { cpu().runOp(code); }
    u8 &mem(u16 at) { return mem().at(at); }

    void ASSERT_REGISTERS(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h, u8 l, u16 sp, u16 pc)
    {
        Registers &regs = ctx->regs();
        REQUIRE(regs.a == a);
        REQUIRE(regs.b == b);
        REQUIRE(regs.c == c);
        REQUIRE(regs.d == d);
        REQUIRE(regs.e == e);
        REQUIRE(regs.f == f);
        REQUIRE(regs.g == g);
        REQUIRE(regs.h == h);
        REQUIRE(regs.l == l);
        REQUIRE(regs.sp == sp);
        REQUIRE(regs.pc == pc);
    }
};