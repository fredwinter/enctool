#ifndef XOR_H
#define XOR_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "key.h"

char *enc_xor(const char *message, key k);
char *dec_xor(const char *message, key k);

#endif