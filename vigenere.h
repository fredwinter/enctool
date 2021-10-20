#ifndef VIGENERE_H
#define VIGENERE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "key.h"
#include "shift.h"

char *enc_vigenere(const char *message, key k);
char *dec_vigenere(const char *message, key k);
void prepare_key(key *k, size_t m_len);

#endif