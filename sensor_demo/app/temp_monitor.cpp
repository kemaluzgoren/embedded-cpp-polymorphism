#include "temp_monitor.hpp"
#include <cstdio>

TempMonitor::TempMonitor(SensorBoard& b)
    : sensor_(b.sensor), alarm_(b.alarm), uart_(b.uart), clock_(b.clock) {}

void TempMonitor::step() {
    if (clock_.millis() - lastSample_ >= kPeriodMs) {
        lastSample_ = clock_.millis();
        sampleAndLog();
    }
}

void TempMonitor::sampleAndLog() {
    float c = sensor_.readCelsius();  // virtual call: host or target sensor
    char msg[48];
    std::snprintf(msg, sizeof msg, "temp=%.1f C%s\n", c, alarmOn_ ? " [ALARM]" : "");
    uart_.print(msg);
    updateAlarm(c);
}

void TempMonitor::updateAlarm(float c) {
    if (!alarmOn_ && c > kHigh) alarmOn_ = true;
    else if (alarmOn_ && c < kLow) alarmOn_ = false;
    alarm_.write(alarmOn_);  // virtual call: LED on host, GPIO on target
}
