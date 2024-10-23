# include "ft_shield.h"

void hash(char *password, char *hash)
{
    int hash_value;
    unsigned int i;

    i = 0;
    hash_value = 0;
    while(i < strlen(password))
    {
        hash_value = (hash_value * SECRET_KEY) + (char)password[i];
        i++;
    }
    snprintf(hash, BUFFER_SIZE, "%08x", hash_value);
}
