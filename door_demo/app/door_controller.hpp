// Door lock logic: PIN entry, auto-relock and lockout. Knows only the HAL interfaces.
#pragma once
#include "../door_hal.hpp"
#include "pin_code.hpp"

class DoorController {
public:
    DoorController(DoorBoard& board, const PinCode& secret);
    void step();  // call periodically from the main loop

private:
    enum class State { Locked, Unlocked, LockedOut };

    void handleKey(char key);
    void submit();
    void enterState(State s);

    IKeypad& keypad_;
    ILock&   lock_;
    IUart&   uart_;
    IClock&  clock_;
    PinCode  secret_;
    PinCode  input_;
    State    state_ = State::Locked;
    char     lastKey_ = 0;
    std::uint8_t  failCount_ = 0;
    std::uint32_t stateSince_ = 0;

    static constexpr std::uint32_t kUnlockMs    = 2000;
    static constexpr std::uint32_t kLockoutMs   = 5000;
    static constexpr std::uint8_t  kMaxAttempts = 3;
};
