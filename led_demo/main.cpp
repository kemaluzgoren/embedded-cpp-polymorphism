#include "app/app.hpp"

int main() {
    Board& board = getBoard();  // hardware is chosen by the linked board_*.cpp
    BlinkApp app(board);
    board.uart.print("boot\n");

    while (board.clock.millis() < 6000) {  // on target: while (true)
        app.step();
        board.clock.delayMs(10);
    }
    board.uart.print("done\n");
}
