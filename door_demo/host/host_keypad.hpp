// Host simulation of a keypad: scripted key presses driven by the virtual clock.
#pragma once
#include "../door_hal.hpp"

class HostKeypad final : public IKeypad {
public:
    explicit HostKeypad(IClock& clock);
    char readKey() override;
private:
    IClock& clock_;
};
