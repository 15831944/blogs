#include <stdio.h>

void fun1 ()
{
    extern int y;
    {
        int y = 1;
        printf("y1 = %d\n", y);
        {
            static int y = 2;
            printf("y2 = %d\n", y);
        }
    }

    {
        extern int y;
        printf("y3 = %d\n", y);
    }
    printf("y4 = %d\n", y);
}

int y = 3;

void fun2 ()
{ 
    printf("y5 = %d\n", y);

    int y = 4;
    printf("y6 = %d\n", y);
}

int scope_test ()
{
    fun1 ();
    fun2 ();
}
