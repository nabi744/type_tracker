#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/login.h"

// Get the current time
time_t get_current_time() {
    return time(NULL);
}

// Updates the trytime for a user in the file
void update_trytime_login(const char *id, int reset, time_t last_attempt) {
    FILE *file = fopen(FILE_PATH_LOGIN, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LOGIN];
    while (fgets(line, MAX_LINE_LOGIN, file)) {
        char file_id[MAX_LINE_LOGIN], password[MAX_LINE_LOGIN];
        int trytime;
        time_t timestamp;

        sscanf(line, "%s %s %d %ld", file_id, password, &trytime, &timestamp);

        if (strcmp(file_id, id) == 0) {
            if (reset || (get_current_time() - timestamp >= 600)) {
                trytime = 0; // Reset if 10 minutes passed or login successful
            } else if (!reset) {
                trytime += 1; // Increment trytime on failure
            }
            timestamp = get_current_time(); // Update timestamp
        }

        fprintf(temp, "%s %s %d %ld\n", file_id, password, trytime, timestamp);
    }

    fclose(file);
    fclose(temp);
    remove(FILE_PATH_LOGIN);
    rename("temp.txt", FILE_PATH_LOGIN);
}

// Main login function
char* login(const char *input) {
    FILE *file = fopen(FILE_PATH_LOGIN, "r");
    if (!file) {
        perror("Error opening file");
        return "error";
    }

    char id[MAX_LINE_LOGIN], password[MAX_LINE_LOGIN];
    sscanf(input, "%s %s", id, password);

    char line[MAX_LINE_LOGIN];
    while (fgets(line, MAX_LINE_LOGIN, file)) {
        char file_id[MAX_LINE_LOGIN], file_password[MAX_LINE_LOGIN];
        int trytime;
        time_t timestamp;

        sscanf(line, "%s %s %d %ld", file_id, file_password, &trytime, &timestamp);

        if (strcmp(file_id, id) == 0) {
            if (strcmp(file_password, password) == 0) {
                if (trytime >= 6) {
                    fclose(file);
                    return "login/fail/tooManyTry";
                }

                update_trytime_login(id, 1, timestamp); // Reset trytime on success
                fclose(file);
                return "login/success";
            } else {
                update_trytime_login(id, 0, timestamp); // Increment trytime on failure
                fclose(file);
                return "login/fail/noPassword";
            }
        }
    }

    fclose(file);
    return "login/fail/noID";
}
