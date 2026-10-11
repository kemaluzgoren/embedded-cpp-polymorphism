#include "stm32_temp_sensor.hpp"

Stm32TempSensor::Stm32TempSensor(ADC_HandleTypeDef* adc) : adc_(adc) {}

float Stm32TempSensor::readCelsius() {
    HAL_ADC_Start(adc_);
    HAL_ADC_PollForConversion(adc_, 10);
    std::uint32_t raw = HAL_ADC_GetValue(adc_);
    HAL_ADC_Stop(adc_);
    float volts = raw * 3.3f / 4095.0f;
    return 25.0f + (volts - 0.76f) / 0.0025f;  // internal sensor, F4 datasheet formula
}
