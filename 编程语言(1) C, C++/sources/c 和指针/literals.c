#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a;

    a = '\177';
    printf("%d\n", a);

    a = 0177;
    printf("%d\n", a);

    a = '177';
    printf("%d\n", a);

    a = L'abc';         //宽字符常量
    printf("%d\n", a);

	int x/*blah blah*/y;

	printf("Blunder\?\?!\?\?");
	printf("(Are you sure??) ??( \n");

	a = '\40';
	printf("%d\n", a);

	a = '\100';
	printf("%d\n", a);

	a = '\x40';
	printf("%d\n", a);

	// a = '\x100';
	// printf("%d\n", a);

	a = '\0123';
	printf("%d\n", a);

	// a = '\x0123';
	// printf("%d\n", a);
    return 0;
}


int stringliteral()
{
	char *str;

	str = "Hello world!";
	*(str + 3) = 'x';	//segment error
	*(str + 0) = 'x';	//bus error
	str = 'x';		//read only
	printf("str = %s\n", str);
}
