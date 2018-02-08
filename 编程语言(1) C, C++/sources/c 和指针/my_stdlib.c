#include <math.h>
#include <string.h>

#include "my_stdlib.h"

/************************
	整数转换为字符串
************************/
char *itoa(int i, char *str)
{
    int mod, div = fabs(i), index = 0;
    char *start, *end, temp;

    do
    {
        mod = div % 10;
        str[index++] = '0' + mod;
        div = div / 10;
    } while(div != 0);

    if (i < 0)
        str[index++] = '-';

    str[index] = '\0';

    for (start = str, end = str + strlen(str) - 1;
        start < end; start++, end--)
    {
        temp   = *start;
        *start = *end;
        *end   = temp;
    }
	
    return str;
}
