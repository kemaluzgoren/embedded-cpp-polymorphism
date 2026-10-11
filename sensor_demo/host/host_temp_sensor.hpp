// Host simulation: temperature ramps 20 -> 35 -> 20 C over 8 s.
#pragma once
#include "../temp_sensor.hpp"

class HostTempSensor final : public ITempSensor {
public:
    explicit HostTempSensor(IClock& clk);
    float readCelsius() override;
private:
    IClock& clk_;
};
