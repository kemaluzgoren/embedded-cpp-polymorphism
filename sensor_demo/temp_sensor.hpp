// New HAL interface for this demo; IGpio/IUart/IClock come from common/hal.hpp.
#pragma once
#include "common/hal.hpp"

struct ITempSensor {
    virtual ~ITempSensor() = default;
    virtual float readCelsius() = 0;
};

// Hardware needed by this application.
struct SensorBoard {
    ITempSensor& sensor;
    IGpio&       alarm;
    IUart&       uart;
    IClock&      clock;
};

// Defined once per platform; selected at link time.
SensorBoard& getSensorBoard();
