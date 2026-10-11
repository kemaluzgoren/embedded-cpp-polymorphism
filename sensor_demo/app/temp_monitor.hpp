// Application layer: knows only the interfaces, not host or target.
#pragma once
#include "../temp_sensor.hpp"

// Samples every 500 ms; alarm on above 30 C, off below 28 C (hysteresis).
class TempMonitor {
public:
    explicit TempMonitor(SensorBoard& b);
    void step();  // call periodically from the main loop
private:
    void sampleAndLog();
    void updateAlarm(float celsius);

    ITempSensor& sensor_;
    IGpio&       alarm_;
    IUart&       uart_;
    IClock&      clock_;
    std::uint32_t lastSample_ = 0;
    bool alarmOn_ = false;

    static constexpr std::uint32_t kPeriodMs = 500;
    static constexpr float kHigh = 30.0f;
    static constexpr float kLow  = 28.0f;
};
