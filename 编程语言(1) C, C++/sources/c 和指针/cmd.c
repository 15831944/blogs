#include <stdio.h>

void process_standard_input(void);
void process_file(char *file_name);

int option_a, option_b;

int main(int argc, char const *argv[])
{ 
    //处理选项参数
    while (*++argv != NULL && **argv == '-')
    {
        switch (*++*argv)
        {
            case 'a':
                option_a = TRUE;
                break;
            case 'b':
                option_b = TRUE;
                break;
        }
    }
    //处理文件名参数
    if (*argv == NULL)
        process_standard_input();
    else
    {
        do {
            process_file(*argv);
        } while(*++argv != NULL);
    }
    return 0;
}
