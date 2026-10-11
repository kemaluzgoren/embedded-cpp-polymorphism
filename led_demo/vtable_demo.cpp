// What virtual does under the hood: a hand-made vtable in plain C style.
#include <cstdio>
#include "common/hal.hpp"
#include "common/host_hal.hpp"

// Function pointer table + one pointer per object.
struct GpioVtbl { void (*write)(void*, bool); bool (*read)(void*); };
struct CGpio { const GpioVtbl* vptr; bool state; };

static void c_write(void* s, bool v) {
    static_cast<CGpio*>(s)->state = v;
    std::printf("C-gpio write(%d)\n", v);
}
static bool c_read(void* s) { return static_cast<CGpio*>(s)->state; }

static const GpioVtbl kVtbl = {c_write, c_read};  // const: lives in flash (.rodata)

int main() {
    CGpio c{&kVtbl, false};
    c.vptr->write(&c, true);  // same as pin->write(true)

    HostClock clk;
    HostLedGpio led(clk);
    IGpio& pin = led;
    pin.write(true);          // compiler generates the same indirect call

    std::printf("sizeof(CGpio)=%zu sizeof(HostLedGpio)=%zu (vptr included)\n",
                sizeof(CGpio), sizeof(HostLedGpio));
}
