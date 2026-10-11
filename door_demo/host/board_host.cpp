#include "../door_hal.hpp"
#include "common/host_hal.hpp"  // reuse HostClock, HostUart
#include "host_keypad.hpp"
#include "host_lock.hpp"

DoorBoard& getDoorBoard() {
    static HostClock  clock;
    static HostUart   uart(clock);
    static HostKeypad keypad(clock);
    static HostLock   lock(uart);
    static DoorBoard  board{keypad, lock, uart, clock};
    return board;
}
