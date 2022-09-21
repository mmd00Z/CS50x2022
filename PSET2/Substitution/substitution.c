#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int is_valid_key(string key);

int main(int argc, string argv[])
{
    if (argc != 2 || is_valid_key(argv[1]))
    {
        printf("Eror\n");
        return 1;
    }

    string plain_txt = get_string("plaintext: ");

    printf("ciphertext: ");
    for (int i = 0; i < strlen(plain_txt); i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (toupper(plain_txt[i]) == 'A' + j)
            {
                plain_txt[i] = toupper(argv[1][j]) + (plain_txt[i] - ('A' + j));
                break;
            }
        }
    }
    printf("%s\n", plain_txt);
    return 0;
}

int is_valid_key(string key)
{
    if (strlen(key) != 26)
    {
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (!isalpha(key[i]) || (key[i] == key[j] && i != j))
            {
                return 1;
            }
        }
    }
    return 0;
}