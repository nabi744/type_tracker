#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/signup.h"

// Check if the ID already exists in the file
bool is_id_exist_signup(const char *id) {
    FILE *file = fopen(FILE_PATH_SIGNUP, "r");
    if (!file) {
        perror("Error opening file");
        return false;
    }

    char line[MAX_LINE_SIGNUP];
    while (fgets(line, MAX_LINE_SIGNUP, file)) {
        char file_id[MAX_LINE_SIGNUP];
        sscanf(line, "%s", file_id);

        if (strcmp(file_id, id) == 0) {
            fclose(file);
            return true; // ID found
        }
    }

    fclose(file);
    return false; // ID not found
}

// Signup function to add a new user
char* signup(const char *input) {
    char id[MAX_LINE_SIGNUP], password[MAX_LINE_SIGNUP];
    sscanf(input, "%s %s", id, password);
    if (is_id_exist_signup(id)) {
        return "signup/fail"; // ID already exists
    }

    FILE *file = fopen(FILE_PATH_SIGNUP, "a");
    if (!file) {
        perror("Error opening file");
        return "error";
    }

    // Add new ID and password to the file with initial trytime and timestamp
    fprintf(file, "%s %s 0 %ld\n", id, password, time(NULL));
    fclose(file);

    return "signup/success"; // Signup successful
}
