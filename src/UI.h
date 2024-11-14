#include <stdio.h>
#include <windows.h>

void pressKey(char key) {
    // Simulate a key press
    keybd_event((BYTE)key, 0, 0, 0);
    // Simulate a key release
    keybd_event((BYTE)key, 0, KEYEVENTF_KEYUP, 0);
}

int main() {
    printf("Pressing the 'A' key...\n");
    pressKey('A'); // Replace 'A' with the desired key
    return 0;
}