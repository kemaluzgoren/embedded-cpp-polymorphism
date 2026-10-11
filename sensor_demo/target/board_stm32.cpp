// Example only: replaces host/board_host.cpp on a real STM32.
#include "stm32_temp_sensor.hpp"
#include "common/stm32_hal.hpp"

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

SensorBoard& getSensorBoard() {
    static Stm32Clock      clock;
    static Stm32Uart       uart(&huart2);
    static Stm32Gpio       alarm(GPIOA, GPIO_PIN_5);
    static Stm32TempSensor sensor(&hadc1);
    static SensorBoard board{sensor, alarm, uart, clock};
    return board;
}
