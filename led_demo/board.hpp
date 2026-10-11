// Hardware needed by the LED/button demo.
#pragma once
#include "common/hal.hpp"

struct Board {
    IGpio&  led;
    IGpio&  button;
    IUart&  uart;
    IClock& clock;
};

// Defined once per platform; selected at link time.
Board& getBoard();
