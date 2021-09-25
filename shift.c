#include "shift.h"

/* This function encrypts a text using a shift cipher
 * with a given distance (int).
 * enc_shift("text", 3) will encrypt the text using the
 * caesar cipher and enc_shift("text", 13) will encrypt
 * the text using the rot-13 cipher.
 */ 
char *enc_shift(const char *message, uint8_t distance)
{

    //check if the distance is between 1 and 25
    if (distance > 25 || distance < 1)
        return NULL;

    size_t len = strlen(message);
    char *enc = malloc(sizeof(char) * len);

    //check if malloc failed
    if (enc == NULL)
    {
        printf("Error allocating memory.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < len; i++)
    {
        unsigned char enc_char;
        unsigned char l_msg_char = tolower(message[i]);

        if (l_msg_char + distance > 'z')
        {
            enc_char = (message[i] + distance) - 26;
        }
        else if (l_msg_char + distance < 'a')
        {
            enc_char = (message[i] + distance) - 26;
        }
        else
        {
            enc_char = message[i] + distance;
        }

        enc[i] = enc_char;
    }
    return enc;
}

/* This function decrypts a text using the shift cipher
 * with a given distance (int).
 * dec_shift("text", 3) will decrypt the text using the
 * caesar cipher and enc_shift("text", 13) will encrypt
 * the text using the rot-13 cipher.
 */
char *dec_shift(const char *message, uint8_t distance)
{

    //check if the distance is between 1 and 25
    if (distance > 25 || distance < 1)
        return NULL;

    size_t len = strlen(message);
    char *dec = malloc(sizeof(char) * len);

    //check if malloc failed
    if (dec == NULL)
    {
        printf("Error allocating memory.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < len; i++)
    {
        unsigned char dec_char;
        unsigned char l_msg_char = tolower(message[i]);

        if (l_msg_char - distance > 'z')
        {
            dec_char = (message[i] - distance) - 26;
        }
        else if (l_msg_char - distance < 'a')
        {
            dec_char = (message[i] - distance) + 26;
        }
        else
        {
            dec_char = message[i] - distance;
        }

        dec[i] = dec_char;
    }
    return dec;
}