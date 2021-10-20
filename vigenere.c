#include "vigenere.h"

/*
 * This function encrypts a text using a vigenère
 * cipher. It works shifting every letter of the
 * message with the shift key corresponding to the
 * subtraction of the vigerère key character's ascii
 * code subtracted by the ascii code of 'a'.
 * 
 * Example:
 * Message char: a
 * Key char    : L
 * enc_vigenere: l
 * 
 * Since 'l' - 'a' is 11, the encrypted char is equal
 * to enc_shift("a", 11), which is 'l'.
 */
char *enc_vigenere(const char *message, key k)
{
    size_t m_len = strlen(message);
    char *enc = malloc(sizeof(char) * m_len + 1);
    if (enc == NULL)
    {
        printf("Error allocating memory.");
        exit(EXIT_FAILURE);
    }
    memset(enc, '\0', m_len + 1);

    if (strlen(k.str) < m_len)
    {
        prepare_key(&k, m_len);
    }

    for (size_t i = 0; i < m_len; i++)
    {
        uint8_t shift_key = tolower(k.str[i]) - 'a';
        if (shift_key == 0)
        {
            enc[i] = message[i];
        }
        else
        {
            char *c = enc_shift(&message[i], shift_key);
            enc[i] = *c;
            free(c);
        }
    }

    free(k.str);
    return enc;
}

/*
 * This function decrypts a text using a vigenère
 * cipher. It works shifting every letter of the
 * message with the shift key corresponding to the
 * subtraction of the vigerère key character's ascii
 * code subtracted by the ascii code of 'a'.
 * 
 * Example:
 * Message char: l
 * Key char    : L
 * dec_vigenere: a
 * 
 * Since 'l' - 'a' is 11, the decrypted char is equal
 * to dec_shift("l", 11), which is 'a'.
 */
char *dec_vigenere(const char *message, key k)
{
    size_t m_len = strlen(message);
    char *dec = malloc(sizeof(char) * m_len + 1);
    if (dec == NULL)
    {
        printf("Error allocating memory.");
        exit(EXIT_FAILURE);
    }
    memset(dec, '\0', m_len + 1);

    if (strlen(k.str) < m_len)
    {
        prepare_key(&k, m_len);
    }

    for (size_t i = 0; i < m_len; i++)
    {
        uint8_t shift_key = tolower(k.str[i]) - 'a';
        if (shift_key == 0)
        {
            dec[i] = message[i];
        }
        else
        {
            char *c = dec_shift(&message[i], shift_key);
            dec[i] = *c;
            free(c);
        }
    }

    free(k.str);
    return dec;
}

/*
 * This function prepares a key for using with
 * vigenere cipher by adding the key characters
 * to the end of the key until it's length is
 * equal to the length of the message.
 * 
 * Example:
 * Message    : attackatdawn
 * Key        : lemon
 * prepare_key: lemonlemonle => strlen(key->str) == strlen(message)
 */
void prepare_key(key *k, size_t m_len)
{
    size_t k_len = strlen(k->str);
    char *k_str = k->str;
    k->str = malloc(m_len);
    for (size_t i = 0; i < m_len; i++)
    {
        k->str[i] = k_str[i % k_len];
    }
}