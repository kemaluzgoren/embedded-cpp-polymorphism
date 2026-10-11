// Host (PC) implementations: simulation instead of real hardware.
#pragma once
#include "hal.hpp"
#include <cstdio>

// Virtual time: delayMs advances the clock instead of sleeping.
class HostClock final : public IClock {
public:
    std::uint32_t millis() override { return now_; }
    void delayMs(std::uint32_t ms) override { now_ += ms; }
private:
    std::uint32_t now_ = 0;
};

class HostUart final : public IUart {
public:
    explicit HostUart(IClock& clk) : clk_(clk) {}
    void write(const char* data, std::size_t len) override {
        std::printf("[%5u ms] UART: ", clk_.millis());
        std::fwrite(data, 1, len, stdout);
    }
private:
    IClock& clk_;
};

// Output pin: prints LED state changes.
class HostLedGpio final : public IGpio {
public:
    explicit HostLedGpio(IClock& clk) : clk_(clk) {}
    void write(bool level) override {
        if (level != state_)
            std::printf("[%5u ms] LED %s\n", clk_.millis(), level ? "ON" : "OFF");
        state_ = level;
    }
    bool read() override { return state_; }
private:
    IClock& clk_;
    bool state_ = false;
};

