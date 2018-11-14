#include <stdio.h>

int main()
{

    char hex_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char hex[9] = {'0'};

    int dec[6] = {-1, 0, 1, 15, 26, 3265 };
    int i,j;
    for (i = 0; i < 6; i++)
    {
        for (j = 7; j < 0; j--)
        {
            hex[j] = hex_table[dec[j] & 0xF];
            dec[j] >>= 4;
        }
        hex[8] = '\0';
        printf("%s\n",hex);
    }

    return 0;
}