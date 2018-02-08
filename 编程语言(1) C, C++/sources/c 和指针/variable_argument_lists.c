#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "my_stdlib.h"
#include "variable_argument_lists.h"

int val_test(void) 
{
	char	*a = "hello";
	int		b = 5;
	char	c = 'a';
	
	my_printf1("sdc", a, b, c);
	my_printf2("Version: %d; Modifier: %s\n", -958, "lingd");
    return 0;
}

void my_printf1(const char *fmt, ...)
{
	va_list ap;
	int d;
	char c, *s;

	va_start(ap, fmt);	// ap 此时指向第一个可变参数
	while (*fmt)
	{
		switch (*fmt++) 
		{
		case 's':						/* string */
			s = va_arg(ap, char *);
			printf("string %s\n", s);
			break;
		case 'd':						/* int */
			d = va_arg(ap, int);
			printf("int %d\n", d);
			break;
		case 'c':						/* char */
			/* need a cast here since va_arg only takes fully promoted types */
			c = (char) va_arg(ap, int);
			printf("char %c\n", c);
			break;
		}
	}
	va_end(ap);
}

void my_printf2(const char *fmt, ...)
{
    char str[100];
    unsigned int len, i, index;
    int iTemp;
    char *strTemp;
    va_list args;

    va_start(args, fmt);
    len = strlen(fmt);
    for (i=0, index=0; i<len; i++)
    {
		/* 原样输出非格式化字符 */
        if (fmt[i] != '%')    
        {
            str[index++] = fmt[i];
        }
        else
        {
			/* 格式化参数 */
            switch(fmt[i+1])
            {
            case 'd':        /* 整型 */
            case 'D':
                iTemp = va_arg(args, int);
                strTemp = itoa(iTemp, str + index);
                index += strlen(strTemp);
                i++;
                break;
            case 's':        /* 字符串 */
            case 'S':
                strTemp = va_arg(args, char*);
                strcpy(str + index, strTemp);
                index += strlen(strTemp);
                i++;
                break;
            default:
                str[index++] = fmt[i];
            }
        }
    }
    str[index] = '\0';
    va_end(args);

    puts(str);        
}
