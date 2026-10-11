#include "../board.hpp"
#include "common/host_hal.hpp"
#include "host_button_gpio.hpp"

Board& getBoard() {
    static HostClock      clock;
    static HostUart       uart(clock);
    static HostLedGpio    led(clock);
    static HostButtonGpio button(clock);
    static Board board{led, button, uart, clock};
    return board;
}
