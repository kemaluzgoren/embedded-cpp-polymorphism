// Example only: not built in the host demo (needs STM32 HAL).
#pragma once
#include "../temp_sensor.hpp"
#include "stm32f4xx_hal.h"

class Stm32TempSensor final : public ITempSensor {
public:
    explicit Stm32TempSensor(ADC_HandleTypeDef* adc);
    float readCelsius() override;
private:
    ADC_HandleTypeDef* adc_;
};
