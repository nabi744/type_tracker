#ifndef SIGNUP_H
#define SIGNUP_H

#include <stdbool.h>

// Define constants
#define MAX_LINE_SIGNUP 256
#define FILE_PATH_SIGNUP "data/user/login.txt"

// Function declarations
char* signup(const char *data);
bool is_id_exist_signup(const char *id);

#endif // SIGNUP_H
