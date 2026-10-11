// Input pin: scripted button presses at fixed times.
#pragma once
#include "common/hal.hpp"

class HostButtonGpio final : public IGpio {
public:
    explicit HostButtonGpio(IClock& clk) : clk_(clk) {}
    void write(bool) override {}  // input pin, ignore writes
    bool read() override {
        auto t = clk_.millis();
        return (t >= 1500 && t < 1600) || (t >= 3500 && t < 3600);
    }
private:
    IClock& clk_;
};
