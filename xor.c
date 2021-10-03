#include "xor.h"

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

char *dec_xor(const char *message, key k)
{
    return enc_xor(message, k);
}