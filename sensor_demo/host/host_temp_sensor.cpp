#include "host_temp_sensor.hpp"

HostTempSensor::HostTempSensor(IClock& clk) : clk_(clk) {}

float HostTempSensor::readCelsius() {
    const std::uint32_t period = 8000;
    std::uint32_t t = clk_.millis() % period;
    float phase = (t < period / 2) ? static_cast<float>(t) / (period / 2)
                                   : static_cast<float>(period - t) / (period / 2);
    return 20.0f + 15.0f * phase;
}
