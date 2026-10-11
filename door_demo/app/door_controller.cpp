#include "door_controller.hpp"
#include <cstdio>

DoorController::DoorController(DoorBoard& board, const PinCode& secret)
    : keypad_(board.keypad), lock_(board.lock), uart_(board.uart),
      clock_(board.clock), secret_(secret) {}

void DoorController::step() {
    char key = keypad_.readKey();
    if (key != 0 && key != lastKey_) handleKey(key);  // rising edge: one press, one event
    lastKey_ = key;

    std::uint32_t elapsed = clock_.millis() - stateSince_;
    if (state_ == State::Unlocked && elapsed >= kUnlockMs) {
        enterState(State::Locked);
    } else if (state_ == State::LockedOut && elapsed >= kLockoutMs) {
        failCount_ = 0;
        enterState(State::Locked);
    }
}

void DoorController::handleKey(char key) {
    if (state_ != State::Locked) return;  // ignore keys while open or locked out
    if (key == '#') {
        submit();
    } else {
        input_.append(key);
    }
}

void DoorController::submit() {
    if (input_ == secret_) {
        failCount_ = 0;
        uart_.print("PIN ok\n");
        enterState(State::Unlocked);
    } else if (++failCount_ >= kMaxAttempts) {
        uart_.print("too many attempts, locked out\n");
        enterState(State::LockedOut);
    } else {
        char msg[32];
        std::snprintf(msg, sizeof msg, "wrong PIN (%u/%u)\n",
                      static_cast<unsigned>(failCount_), static_cast<unsigned>(kMaxAttempts));
        uart_.print(msg);
    }
    input_.clear();
}

void DoorController::enterState(State s) {
    state_ = s;
    stateSince_ = clock_.millis();
    if (s == State::Unlocked) lock_.unlock();  // virtual call: drives the real lock
    else                      lock_.lock();
}
