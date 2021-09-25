#ifndef CHECK_DIGIT_H
#define CHECK_DIGIT_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

bool input_is_digit(char *arg);

//define a key struct to hold key information
typedef struct {
    bool is_digit;
    union {
        int num;
        char *str;
    };
} key;

#endif