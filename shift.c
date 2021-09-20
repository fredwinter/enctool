#include "shift.h"

// This function encrypts a text using a shift cipher
// with a given distance (int).
// enc_shift("text", 3) will encrypt the text using the
// caesar cipher.
char *enc_shift(char *text, uint8_t distance)
{
    if (distance > 25 || distance < 1)
    {
        return NULL;
    } 

    int len = strlen(text);
    char *enc = malloc(sizeof(char) * len);

    if (enc == NULL)
    {
        printf("Error allocating memory.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < len; i++)
    {
        char enc_char = text[i] + distance;

        if (tolower(enc_char) > 'z')
        {
            enc_char -= 26;
        }
        else if (tolower(enc_char) < 'a')
        {
            enc_char += 26;
        }

        enc[i] = enc_char;
    }
    return enc;
}

// This function decrypts a text using the shift cipher
// with a given distance (int).
// dec_shift("text", 3) will decrypt the text using the
// caesar cipher.
char *dec_shift(char *text, uint8_t distance)
{
    if (distance > 25 || distance < 1)
    {
        return NULL;
    }

    int len = strlen(text);
    char *dec = malloc(sizeof(char) * len);

    if (dec == NULL)
    {
        printf("Error allocating memory.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < len; i++)
    {
        char dec_char = text[i] - distance;

        if (tolower(dec_char) > 'z')
        {
            dec_char -= 26;
        }
        else if (tolower(dec_char) < 'a')
        {
            dec_char += 26;
        }

        dec[i] = dec_char;
    }
    return dec;
}