#include <stdio.h>
#include <windows.h>
#include "UI.h"

// Main function
int main() {
    int color = 1;  // Initial color
    drawSquare(color);  // Draw the initial square

    printf("\nPress 'a' to change color. Press 'q' to quit.");

    while (1) {
        if (_kbhit()) {  // Check if a key is pressed
            char ch = _getch();
            if (ch == 'a' || ch == 'A') {
                color = (color % 15) + 1;  // Cycle through colors (1 to 15)
                drawSquare(color);  // Redraw the square with the new color
            } else if (ch == 'q' || ch == 'Q') {
                break;  // Exit if 'q' is pressed
            }
        }
    }

    setCursorPosition(0, SQUARE_Y + SQUARE_SIZE + 2);  // Move cursor after square
    return 0;
}
