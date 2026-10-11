// Example only: built instead of host/board_host.cpp on a real STM32.
#include "../board.hpp"
#include "common/stm32_hal.hpp"

extern UART_HandleTypeDef huart2;

Board& getBoard() {
    static Stm32Clock clock;
    static Stm32Uart  uart(&huart2);
    static Stm32Gpio  led(GPIOA, GPIO_PIN_5);
    static Stm32Gpio  button(GPIOC, GPIO_PIN_13);
    static Board board{led, button, uart, clock};
    return board;
}
