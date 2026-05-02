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
        regs().a = 0;
        regs().b = 0;
        regs().c = 0;
        regs().d = 0;
        regs().e = 0;
        regs().f = 0;
        regs().g = 0;
        regs().h = 0;
        regs().l = 0;
        regs().pc = 0;
        regs().sp = 0;
        cpu().setCycles(0);
    }

    // Shortcut getters
    Registers &regs() { return ctx->regs(); }
    CPU &cpu() { return ctx->cpu(); }
    u8 *mem() { return ctx->mem().getMem(); }
    void runOp(u8 code)
    {
        std::cout << "Running test for code " << Common::toHexStr(code) << std::endl;
        mem(regs().pc) = code;

        cpu().tick();
        while (!cpu().getQueue().empty() || cpu().getStallCycles() > 0)
        {
            cpu().tick();
        }

        // cpu().setCycles(cpu().getCycles() - 1);
    }
    void runCBPrefixOp(u8 code)
    {
        mem(regs().pc) = 0xCB;
        mem(regs().pc + 1) = code;
        runOp(0xCB);
    }
    u8 &mem(u16 at) { return mem().at(at); }
    u64 ticks() { return cpu().getCycles(); }

    void ASSERT_REGISTERS(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h, u8 l, u16 sp, u16 pc)
    {
        REQUIRE(regs().a == a);
        REQUIRE(regs().b == b);
        REQUIRE(regs().c == c);
        REQUIRE(regs().d == d);
        REQUIRE(regs().e == e);
        REQUIRE(regs().f == f);
        REQUIRE(regs().g == g);
        REQUIRE(regs().h == h);
        REQUIRE(regs().l == l);
        REQUIRE(regs().sp == sp);
        REQUIRE(regs().pc == pc);
    }
};