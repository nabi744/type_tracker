#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define SQUARE_SIZE 5  // Size of the square (5x5)
#define SQUARE_X 10    // X position of the square
#define SQUARE_Y 5     // Y position of the square

// Function to set console cursor position
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to set text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to draw a square with a specific color
void drawSquare(int color) {
    setColor(color);
    for (int i = 0; i < SQUARE_SIZE; i++) {
        setCursorPosition(SQUARE_X, SQUARE_Y + i);
        for (int j = 0; j < SQUARE_SIZE; j++) {
            printf("*");
        }
    }
    setColor(7);  // Reset color to default
}
