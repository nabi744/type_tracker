
#include <stdio.h>
#include <string.h>
#include "include/login.h"

int main() {
    char input[MAX_LINE_LOGIN];
    printf("Enter login (id password): ");
    fgets(input, MAX_LINE_LOGIN, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character

    const char *result = login(input);
    printf("%s\n", result);

    return 0;
}
