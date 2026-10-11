#include "app/door_controller.hpp"

int main() {
    DoorBoard& board = getDoorBoard();  // hardware chosen by the linked board file
    DoorController door(board, PinCode("1234"));
    board.uart.print("boot\n");

    while (board.clock.millis() < 20000) {  // on target: while (true)
        door.step();
        board.clock.delayMs(10);
    }
}
