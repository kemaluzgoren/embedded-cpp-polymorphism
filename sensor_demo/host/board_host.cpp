#include "host_temp_sensor.hpp"
#include "common/host_hal.hpp"  // reuse HostClock, HostUart, HostLedGpio

SensorBoard& getSensorBoard() {
    static HostClock      clock;
    static HostUart       uart(clock);
    static HostLedGpio    alarm(clock);
    static HostTempSensor sensor(clock);
    static SensorBoard board{sensor, alarm, uart, clock};
    return board;
}
