#ifndef MAIN_H
#define MAIN_H
#include <stdbool.h>
#include <unistd.h>

bool input_is_digit(char *arg);

typedef struct {
    bool is_digit;
    union {
        int num;
        char *str;
    };
} key;

#endif