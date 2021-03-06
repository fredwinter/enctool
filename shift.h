#ifndef SHIFT_H
#define SHIFT_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *enc_shift(const char *message, uint8_t distance);
char *dec_shift(const char *message, uint8_t distance);

#endif