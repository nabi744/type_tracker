#ifndef LOGIN_H
#define LOGIN_H

#include <time.h>

// Define constants
#define MAX_LINE_LOGIN 256
#define FILE_PATH_LOGIN "./data/user/login.txt"
// #define FILE_PATH_LOGIN "/Users/seunggeon/Documents/vscode/type_tracker/data/user/login.txt"

// Function declarations
char* login(const char *input);
void update_trytime_login(const char *id, int reset, time_t last_attempt);
time_t get_current_time();

#endif // LOGIN_H
