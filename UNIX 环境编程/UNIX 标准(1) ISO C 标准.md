ISO C 库可以分成24个区（头文件）

| 头文件 |  说明  | 库函数 |
| - | - | - |
| assert.h |  | 1 |
| complex.h |  | 2 |
| ctype.h | 字符属性分类和转换 | 3 |
| errno.h | 出错码 | 4 |
| fenv.h |  | 5 |
| float.h | 浮点常量及特性 | 6 |
| inttypes.h |  | 7 |
| iso646.h |  | 8 |
| limits.h | 实现常量 | 9 |
| locale.h |  | 10 |
| math.h |  | 11 |
| setjmp.h |  | 12 |
| signal.h | 信号 | 13 |
| stdarg.h | 可变长度参数表 | 14 |
| stdbool.h |  | 15 |
| stddef.h | 标准定义 | 16 |
| stdint.h |  | 17 |
| stdio.h | 标准 I/O 库，其实现依赖于操作系统 | 18 |
| stdlib.h | 实用函数 | 19 |
| string.h | 字符串操作 | 20 |
| tgmath.h |  | 21 |
| time.h | 时间和日期 | 22 |
| wchar.h |  | 23 |
| wctype.h | 宽字符属性分类和转换 | 24 |

# 3. ctype.h

标准属性判断函数

isalnum		isalpha		iscntrl		isdigit		
isxdigit	isgraph		isprint		ispunct
islower		isupper		isspace		isblank

标准属性转换函数

tolower		toupper

glibc 扩展的函数

isctype		isascii		toascii

# 18. stdio.h

FILE EOF NULL size_t

fopen fclose fflush frepoen fwide FOPEN_MAX FILENAME_MAX

setvbuf setbuf BUFSIZ _IOFBF _IOLBF _IONBF

stdin stdout stderr

fseek ftell rewind fgetops fsetpos fpos_t SEEK_SET SEEK_CUR SEEK_END

fgetc fgetwc getc getwc getchar getwchar ungetc ungetwc

fgets fgetws gets

fscanf fwscanf scanf wscanf sscanf swscanf

fputc fputwc putc putwc putchar putwchar

fputs fputws puts

fprintf printf sprintf snprintf fwprintf wprintf swprintf

vfprintf vprintf vsprintf vfscanf vscanf vsscanf vfwprintf vwprintf vswprintf vfwscanf vwscanf vswscanf

fread fwrite

feof ferror clearerr

remove rename

tmpfile tmpnam L_tmpnam TMP_MAX

perror
