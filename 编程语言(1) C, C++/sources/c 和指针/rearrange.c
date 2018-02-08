#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 20         // 列标号最大数量
#define MAX_INPUT 1000

int read_column_numbers( int columns[], int max );
void rearrange( char *output, char const *input, int n_columns, int const columns[]);

int main( void )
{
    int n_columns;          // 处理的列标号数量
    int columns[MAX_COLS];  // 处理的列标号数组
    char input[MAX_INPUT];
    char output[MAX_INPUT];

    printf("rearrange v1.1\n");

    // 读取列标号(首行)
    n_columns = read_column_numbers( columns, MAX_COLS );

    // 读取字符串(剩余各行)
    while (gets( input) != NULL )
        rearrange( output, input, n_columns, columns );

    return EXIT_SUCCESS;
}

/**********************************
*   参数:
*   列标号数组
*   列标号数组最大长度
***********************************/
int read_column_numbers(int columns[], int max)
{
    int num = 0;
    int ch;

    printf("Please Start Input : \n");

    // 从标准输入中读取列标号
    while (num < max && scanf("%d", &columns[num]) == 1 && columns[num] >= 0 )
    {
        printf("columns[%d] = %d\n", num, columns[num]);
        num += 1;
    }
    printf("num = %d\n", num);

    // 测试结果
    #if 0
    if (num % 2 != 0)
    {
        puts("Error: Last colnum number is not paired.");
        exit(EXIT_FAILURE);
    }
    #endif

    // 将当前文件偏移量移到行尾
    while ((ch = getchar()) != EOF && ch != '\n')
    {
        printf("ch = %c\n", ch);
    }

    return num;
}

/**********************************
*   重排一行输入
***********************************/
void rearrange(char *output, char const *input, int n_columns, int const columns[])
{
    int col;        //每对列表号起始位置
    int output_col = 0;
    int len;
    int nchars;

    len = strlen(input);
    printf("Input = %s Length = %d\n", input, len);

    // 每对列标号
    for (col=0; col<n_columns; col+=2)
    {
        // 每对列标号间的字符数
        if (col < n_columns - 1)
        {
            nchars = columns[col+1] - columns[col] + 1;
            printf("nchars1 = %d\n", nchars);
        }
        else
        {
            nchars = len - columns[col];
            printf("nchars2 = %d\n", nchars);
        }

        // 输入的列起始不能超过输入行的长度
        if (columns[col] >= len)
            continue;

        // 输出的列起始不能超过最大长度
        if (output_col == MAX_INPUT - 1)
            break;

        // 输出的列结束不能超过最大长度
        if (output_col + nchars > MAX_INPUT - 1)
            nchars = MAX_INPUT - output_col - 1;

        // 输入行的列结束不能超过输入行的长度
        if (columns[col] + nchars - 1 >= len)
            nchars = len - columns[col];

        // 输入的列结束可以超过输入行长度
        // strcpy(output + output_col, input + columns[col]);
        strncpy(output + output_col, input + columns[col], nchars);
        output_col += nchars;
    }
    output[output_col] = '\0';

    printf("Output = %s\n", output);
}
