#include "app/temp_monitor.hpp"

int main() {
    SensorBoard& board = getSensorBoard();  // hardware chosen by the linked board file
    TempMonitor monitor(board);

    while (board.clock.millis() < 8000) {   // on target: while (true)
        monitor.step();
        board.clock.delayMs(10);
    }
}
