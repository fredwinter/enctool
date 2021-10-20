#include "xor.h"

/*
 * This function encrypts a text using the xor
 * cipher. It works applying the exclusive
 * disjunction binary operation.
 * 
 * Example:
 * Message: label = 0110110001100001011000100110010101101100
 * Key    : 13    = 0000110100001101000011010000110100001101
 * enc_xor: aloha = 0110000101101100011011110110100001100001
 */
char *enc_xor(const char *message, key k)
{
    size_t k_len = 0;
    size_t m_len = strlen(message);

    if (!k.is_digit)
    {
        k_len = strlen(k.str);
    }

    char *enc = malloc((sizeof(char) * m_len) + 1);
    if (enc == NULL)
    {
        printf("Error allocating memory.");
        exit(EXIT_FAILURE);
    }
    memset(enc, '\0', m_len + 1);

    for (size_t i = 0; i < m_len; i++)
    {
        if (k.is_digit)
        {
            enc[i] = message[i]^k.num;
        }
        else
        {
            enc[i] = message[i]^k.str[i%k_len];
        }
    }

    return enc;
}

/*
 * This function decrypts a text using the xor
 * cipher. It works applying the exclusive
 * disjunction binary operation.
 * 
 * Since the operation is the same we do when
 * encrypting the text, this function just calls
 * the enc_xor().
 * 
 */
char *dec_xor(const char *message, key k)
{
    return enc_xor(message, k);
}