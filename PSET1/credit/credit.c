#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    long number = get_long("number: ");
    char *str_num = malloc(4 * sizeof(int));
    sprintf(str_num, "%li", number);

    int n = strlen(str_num);
    int checksum = 0;
    for (int i = 0; i < n; i++)
    {
        checksum += (i % 2 != n % 2) ? str_num[i] - 48 : ((str_num[i] - 48) * 2 > 9) ? (((str_num[i] - 48) * 2) % 10) + 1 :
                    (str_num[i] - 48) * 2;
    }

    if (checksum % 10 == 0)
    {
        if (str_num[0] == '4' && (n == 13 || n == 16))
        {
            printf("VISA\n");
        }
        else if (n == 15 && str_num[0] == '3' && (str_num[1] == '4' || str_num[1] == '7'))
        {
            printf("AMEX\n");
        }
        else if (n == 16 && str_num[0] == '5' && (str_num[1] == '1' || str_num[1] == '2' || str_num[1] == '3' || str_num[1] == '4'
                 || str_num[1] == '5'))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}