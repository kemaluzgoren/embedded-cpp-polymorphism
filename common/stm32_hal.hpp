// Example only: STM32 implementations shared by all demos (needs STM32 HAL).
#pragma once
#include "hal.hpp"
#include "stm32f4xx_hal.h"

class Stm32Gpio final : public IGpio {
public:
    Stm32Gpio(GPIO_TypeDef* port, std::uint16_t pin) : port_(port), pin_(pin) {}
    void write(bool level) override {
        HAL_GPIO_WritePin(port_, pin_, level ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    bool read() override { return HAL_GPIO_ReadPin(port_, pin_) == GPIO_PIN_SET; }
    void toggle() override { HAL_GPIO_TogglePin(port_, pin_); }  // hardware toggle
private:
    GPIO_TypeDef* port_;
    std::uint16_t pin_;
};

class Stm32Uart final : public IUart {
public:
    explicit Stm32Uart(UART_HandleTypeDef* h) : h_(h) {}
    void write(const char* d, std::size_t n) override {
        HAL_UART_Transmit(h_, reinterpret_cast<const std::uint8_t*>(d),
                          static_cast<std::uint16_t>(n), HAL_MAX_DELAY);
    }
private:
    UART_HandleTypeDef* h_;
};

class Stm32Clock final : public IClock {
public:
    std::uint32_t millis() override { return HAL_GetTick(); }
    void delayMs(std::uint32_t ms) override { HAL_Delay(ms); }
};
