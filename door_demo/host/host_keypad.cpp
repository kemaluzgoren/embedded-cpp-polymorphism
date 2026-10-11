#include "host_keypad.hpp"
#include <cstring>

namespace {
constexpr std::uint32_t kKeyStepMs = 200;   // time between two key presses
constexpr std::uint32_t kKeyHoldMs = 50;    // how long a key stays pressed

struct Entry{
    std::uint32_t startMs;
    const char* keys;
};

const Entry kScript[] = {
    {500,   "0000#"},  // wrong PIN
    {2000,  "1234#"},  // correct PIN
    {7000,  "1111#"},  // wrong 1
    {8000,  "2222#"},  // wrong 2
    {9000,  "3333#"},  // wrong 3 -> lockout
    {10000, "1234#"},  // ignored: locked out
    {15500, "1234#"},  // correct PIN after lockout
};

}

HostKeypad::HostKeypad(IClock& clock) : clock_(clock) {}

char HostKeypad::readKey() {
    std::uint32_t now = clock_.millis();
    for(const Entry& e : kScript) {
        if(now < e.startMs) continue;
        std::uint32_t dt = now - e.startMs;
        std::size_t idx = dt / kKeyStepMs;
        if(idx < std::strlen(e.keys) && dt % kKeyStepMs < kKeyHoldMs)
            return e.keys[idx];
    }
    return 0; 
}
