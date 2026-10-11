// Application layer: depends only on hal.hpp, unaware of host/target.
#pragma once
#include "../board.hpp"
#include <cstdio>

class Led {
public:
    explicit Led(IGpio& pin) : pin_(pin) {}
    void on()     { pin_.write(true); }
    void off()    { pin_.write(false); }
    void toggle() { pin_.toggle(); }  // virtual call: runs the real type's toggle
private:
    IGpio& pin_;
};

// Rising-edge detector (no debounce, enough for the demo).
class Button {
public:
    explicit Button(IGpio& pin) : pin_(pin) {}
    bool wasPressed() {
        bool now = pin_.read();
        bool edge = now && !last_;
        last_ = now;
        return edge;
    }
private:
    IGpio& pin_;
    bool last_ = false;
};

// Button press switches the blink period; events are logged over UART.
class BlinkApp {
public:
    explicit BlinkApp(Board& b)
        : led_(b.led), button_(b.button), uart_(b.uart), clock_(b.clock) {}

    void step() {
        if (button_.wasPressed()) {
            period_ = (period_ == 500) ? 100 : 500;
            char msg[64];
            std::snprintf(msg, sizeof msg, "button pressed, period=%u ms\n",
                          static_cast<unsigned>(period_));
            uart_.print(msg);
        }
        auto now = clock_.millis();
        if (now - lastToggle_ >= period_) {
            led_.toggle();
            lastToggle_ = now;
        }
    }
private:
    Led     led_;
    Button  button_;
    IUart&  uart_;
    IClock& clock_;
    std::uint32_t period_ = 500, lastToggle_ = 0;
};
