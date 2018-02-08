#include <assert.h>
#include <ctype.h>
#include <float.h>

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "alloc.h"
#include "data.h"
#include "literal.h"
#include "prototype.h"

#undef malloc

/***********************************
	程序 13.5 十六进制整数转换为字符
***********************************/
void binary_to_ascii_v2(unsigned int value)
{
	unsigned int quotient, remainder;

	quotient = value / 16;
	if (quotient != 0)
		binary_to_ascii_v2(quotient);

	remainder = value % 16;
	if (remainder < 10)
		putchar(remainder + '0')
	else
		putchar(remainder - 10 + 'A');

	putchar("0123456789ABCDEF"[value % 16])
}

/*****************************
	程序 13.4 按比例打印星号
*****************************/
void print_stars(int n)
{
	n = 10 - (n + 5) / 10;
	printf("%s\n", "**********"[n]);
}

/*************************************************
	程序 13.1 函数指针 回调函数 callback function
*************************************************/
void compare_all_kinds_of_data(void)
{
	Node desired_node;
	desired_node = search_list(root, &desired_value, compare_ints);
	desired_node = search_list(root, "desired_value", strcmp);
}

Node *search_list(Node *node, void const *value, int (*compare)(void const *, void const *))
{
	while (node != NULL)
	{
		if (compare(&node->value, value) == 0)
			break;
		node = node->link;
	}
	return node;
}

int compare_ints(void const *a, void const *b)
{
	if (*(int *)a == *(int *)b)
		return 0;
	else
		return 1;
}

/*************************
	程序 11.3 复制字符串
*************************/
char *string_duplicate(char const *string)
{
	char *new_string;

	new_string = malloc(strlen(string) + 1);

	if (new_string != NULL)
		strcpy(new_string, string);

	return new_string;
}

/***********************
	程序 11.2 整型排序
***********************/
int alloc_array_sort()
{
	char_type_count();

	int *array;
	int n_values;
	int i;

	printf("How many values are there?\n");
	if (scanf("%d", &n_values) != 1 || n_values <= 0)
	{
		printf("Illegal number of values.\n");
		exit(EXIT_FAILURE);
	}

	array = MALLOC(n_values, int);
	if (array == NULL)
	{
		printf("Can't get memory for that many values.\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < n_values; i += 1)
	{
		printf("? ");
		if (scanf("%d", array + i) != 1)
		{
			printf("Error Reading value #%d\n", i);
			free(array);
			exit(EXIT_FAILURE);
		}
	}

	qsort(array, n_values, sizeof(int), compare_integers);

	for (i = 0; i < n_values; i += 1)
		printf("%d\n", array[i]);

	free(array);
	return EXIT_SUCCESS;
}

/***********************
	程序 11.2 整型排序
***********************/
int compare_integers(void const *a, void const *b)
{
	register int const *pa = a;
	register int const *pb = b;

	return *pa > *pb ? 1 : *pa < *pb ? -1 : 0;
}

/*********************************
	程序 11.1 带错误检查的内存分配
*********************************/
void *alloc(size_t size)
{
	void *new_mem;

	new_mem = malloc(size);
	if (new_mem == NULL)
	{
		printf("Out of Memory!\n");
		exit(1);
	}
	return new_mem;
}

/********************************
	编程练习 9.16 以给定格式输出
********************************/
int specified_format_output(char *format_string, char const *digit_string)
{
	char const *d_p, *f_p;

	d_p =  digit_string + strlen(digit_string) - 1;
	f_p = format_string + strlen(format_string) - 1;

	printf("dp = %c fp = %c\n", *d_p, *f_p);

	do
	{
		if (*f_p == '#')
			*format_string-- = *digit_string--;
		if (*f_p == ',' || *f_p == '.')
			format_string--;
	}while  (f_p > format_string);

	printf("string %s\n", format_string);
	return EXIT_SUCCESS;
}

/************************************
	编程练习 9.15 给数额加逗号进行分隔
************************************/
void dollars_insert_comma(register char *dst, register char const *src)
{
	int len;

	if (dst == NULL || src == NULL)
		return;

	*dst++ = '$';
	len = strlen(src);

	/*小数点前的数字*/
	if (len > 2)
	{
		int i;

		for (i = len - 2; i > 0;)
		{
			*dst++ = *src++;
			if (--i > 0 && i % 3 == 0)
				*dst++ = ',';
		}
	}
	else
		*dst++ = '0';

	/*小数点后的数字*/
	*dst++ = '.';
	*dst++ = len < 2 ? '0' : *src++;
	*dst++ = len < 1 ? '0' : *src;
	*dst = 0;
}

/*******************************
	编程练习 9.14 解密
*******************************/
void decrypt_key(char *data, char const *key)
{
	int i, j;

	for (i = 0; i < strlen(data); i++)
	{
		for (j = 0; j < strlen(key); j++)
		{
			if (data[i] == key[j])
			{
				data[i] = 'a' + j;
				break;
			}
		}
	}
	printf("decrypt_data = %s\n", data);
}

/*******************************
	编程练习 9.13 加密
*******************************/
void encrypt_key(char *data, char const *key)
{
	int i, offset;

	for (i = 0; i < strlen(data); i++)
	{
		if (islower(data[i]))
		{
			offset = data[i] - 'a';
			data[i] = key[offset];
		}
	}
	printf("encrypt_data = %s\n", data);
}

/*******************************
	编程练习 9.12 由单词生成密匙
*******************************/
int delete_repeated_chars(char *key)
{
	char *i, *j;
	i = key;
	/*依次轮询每个字符,删除其后与其相同的每个字符*/
	while (*i != '\0')
	{
		j = i + 1;
		while (*j != '\0')
		{
			if (*i == *j)
				memmove(j, j + 1, strlen(j)); //删除当前的一个重复字符,内存操作应包含末尾'\0'字符
			else
				j++;
		}
		i++;
	}
	printf("key = %s\n", key);
	return 0;
}

int prepare_key(char *key)
{
	char *i, *j;
	unsigned int index, len, start, ex;
	char alpha;

	printf("key0 = %s\n", key);

	/*依次轮询每个字符,删除其后与其相同的每个字符*/
	i = key;
	while (*i != '\0')
	{
		j = i + 1;
		while (*j != '\0')
		{
			if (*i == *j)
				memmove(j, j + 1, strlen(j)); //删除当前的一个重复字符,内存操作应包含末尾'\0'字符
			else
				j++;
		}
		i++;
	}
	printf("key1 = %s\n", key);

	start = len = strlen(key);
	alpha = 'a';
	while (start < 26)
	{
		for (index = 0; index < len; index++)
		{
			if (alpha == key[index])
			{
				alpha++;
				ex = TRUE;
			}
		}
		if (ex != TRUE)
			key[start++] = alpha++;
		ex = FALSE;
	}
	printf("key2 = %s\n", key);
	return 0;
}

/**************************
	编程练习 9.11 单词计数
**************************/
int string_word_count(char *string, char *word)
{
	static char const whitespace[] = " \t\f\r\v\n";
	char *token;
	int count = 0;

	for (token = strtok(string, whitespace); token != NULL; token = strtok(NULL, whitespace))
	{
		printf("token = %s\n", token);
		if (strcmp(token, word) == 0)
			count++;
	}
	printf("count = %d\n", count);
	return EXIT_SUCCESS;
}

/***********************
	编程练习 9.10 回文
***********************/
int palindrome_v2(char *string)
{
	char *front, *rear;

	front = string;
	rear  = string + strlen(string) - 1;
	while (front < rear)
	{
		while (!isalpha(*front))
			front++;
		while (!isalpha(*rear))
			rear--;

		printf("front = %c rear = %c\n", *front, *rear);
		if (isupper(*front))
		{
		 	if ((*front != *rear) && (*front + 32 != *rear))
				return FALSE;
		}
		else if (islower(*front))
		{
			if ((*front != *rear) && (*front - 32 != *rear))
				return FALSE;
		}
		front++, rear--;
	}
	printf("TRUE\n");
	return TRUE;
}

/***************************
	编程练习 9.9 字符计数
***************************/
int string_count_chars(char const *str, char const *chars)
{
	int count = 0;
	char const *ch;

	while (*str != '\0')
	{
		// printf("str = %c\n", *str);
		for (ch = chars; ch < chars + strlen(chars); ch ++)
		{
			if (*str == *ch)
				count++;
		}
		str++;
	}
	return count;
}

/***************************
	编程练习 9.8 查找字符
***************************/
char const *str_n_chr(char const *str, int ch, int which)
{
	char const *p;
	int cnt;

	for (p = str; p < p + strlen(str); p++)
	{
		if (*p == ch)
			cnt++;
		if (which ==cnt)
			return p;
	}
	return NULL;
}

/***************************
	编程练习 9.7 查找字符
***************************/
char const *str_r_chr(char const *str, int ch)
{
	char const *p;
	for (p = str + strlen(str); p > str;)
	{
		if (*--p == ch)
			return p + 1;
	}
	return NULL;

}
/****************************************
	编程练习 9.6 指向字符串结束的字符串复制
****************************************/
char *string_copy_end_v1(char *dst, char *const src)
{
	strcpy(dst, src);
	return dst + strlen(dst);
}

char * string_copy_end_v2(register char *dst, register char const *src)
{
	while ((*dst++ = *src++) != '\0')
		;
	return dst - 1;
}

/******************************
	编程练习 9.5 安全的字符串连接
******************************/
void string_n_catinate_safe(char *dst, char const *src, int dest_len)
{
	if (dest_len >= strlen(dst) + strlen(src))
		strncat(dst, src, dest_len);
	else if (dest_len >= strlen(dst))
	{
		strncat(dst, src, dest_len - strlen(dst));
		dst[sizeof(dst) - 1] = '\0';
	}
}

/******************************
	编程练习 9.4 安全的字符串连接
******************************/
void string_catinate_safe(char *dst, char const *src)
{
	if (sizeof(dst) >= strlen(dst) + strlen(src))
		strcat(dst, src);
	else if (sizeof(dst) >= strlen(dst))
	{
		strncat(dst, src, sizeof(dst) - strlen(dst));
		dst[sizeof(dst) - 1] = '\0';
	}
}

/******************************
	编程练习 9.3 安全的字符串复制
******************************/
void string_copy_safe(char *dst, char const *src)
{
	if (sizeof(dst) >= sizeof(src))
		strcpy(dst, src);
	else
	{
		strncpy(dst, src, sizeof(dst) - 1);
		dst[sizeof(dst) - 1] = '\0';
	}
}

/******************************
	编程练习 9.2 安全的字符串长度
******************************/
size_t string_length_safe(char const *string, int size)
{
	register size_t length;

	for (length = 0; length < size; length += 1)
		if (*string++ == '\n')
			break;
	return length;
}

/******************************
	编程练习 9.1 字符类型统计
******************************/
void char_type_count(void)
{
	int ch;
	int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0;

	while ((ch = getchar()) != EOF)
	{
		if (iscntrl(ch))
			a++;
		if (isspace(ch))
			b++;
		if (isdigit(ch) || isxdigit(ch))
			c++;
		if (islower(ch))
			d++;
		if (isupper(ch))
			e++;
		if (ispunct(ch))
			f++;
		if (isprint(ch))
			g++;
	}
	printf("cntrl %d\n", a);
	printf("space %d\n", b);
	printf("digit %d\n", c);
	printf("lower %d\n", d);
	printf("upper %d\n", e);
	printf("punct %d\n", f);
	printf("print %d\n", g);
}

/**********************
	程序 9.3 提取标记
**********************/
void print_tokens_v1(char *line)
{
	static char whitespace[] = " \t\f\r\v\n";
	char *token;

	for (token = strtok(line, whitespace); token != NULL; token = strtok(NULL, whitespace))
		printf("Next token is %s\n", token);
}

void print_tokens_v2(char *line)
{
	static char whitespace[] = " \t\f\r\v\n";
	char *token;

 	token = strtok(line, whitespace);
    printf("token = %s\n", token);

    while(token != NULL)
    {
        token = strtok(NULL, whitespace);
        printf("token = %s\n", token);
    }
}

/******************************
	程序 9.2 从右侧查找子串
******************************/
char *string_right_string(char const *s1, char const *s2)
{
	register char *last;		//上一次查找起始位置
	register char *current;		//当前查找起始位置

	last = NULL;

	if (*s2 != '\0')
	{
		current = strstr(s1, s2);
		while (current != NULL)
		{
			last = current;
			current = strstr(last + 1, s2);
		}
	}
	return last;
}

/***************************
	编程练习 8.4 矩阵乘法
***************************/
void matrix_multiply(int *m1, int *m2, register int *r, int x, int y, int z)
{
	register int *m1_pointer;
	register int *m2_pointer;
	register int k;
	int row;
	int column;

	for (row = 0; row < x; row ++)
	{
		for (column = 0; column < z; column ++)
		{
			m1_pointer = m1 + row * y;
			m2_pointer = m2 + column;
			*r = 0;

			for (k = 0; k < y; k += 1)
			{
				*r += *m1_pointer * *m2_pointer;
				m1_pointer += 1;
				m2_pointer += z;
			}
			r++;
		}
	}
}


/***************************
	编程练习 8.3 单位矩阵
***************************/
int identity_matrix(int *matrix[], int size)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (i != j)
			{
				if (matrix[i][j] != 0)
					break;
			}
			else
			{
				if (matrix[i][j] != 1)
					break;
			}
		}
	}
	if (i == size && j == size)
		return TRUE;
	else
		return FALSE;
}

/***************************
	编程练习 8.2 个人所得税
***************************/
double single_tax(double income)
{
	static double income_limits[] = {   0,  23350,   56550,  117950,  256500, DBL_MAX};
	static float  base_tax[]      = {   0, 3502.5, 12798.5, 31832.5, 81710.5};
	static float  percentage[]    = {0.15,   0.28,    0.31,    0.36,   0.396};

	int category;

	for (category = 1; income > income_limits[category]; category += 1)
		;
	category -= 1;
	return base_tax[category] + percentage[category] * (income - income_limits[category]);
}

/***********************
	问题 8.7.4 回文
***********************/
void palindrome(char *buffer, int SIZE)
{
	char *front, *rear;

	front = buffer;
	rear  = buffer + SIZE - 1;
	while (front < rear)
	{
		printf("%c %c\n", *front, *rear);
		if (*front++ != *rear--)
			break;
	}
	if (front >= rear)
		printf("It is a palindrome!\n");
}

/***********************
	程序 8.2 关键字查找
***********************/
int lookup_keyword(char const * const desired_word, char const *keyword_table[], int const size)
{
	char const **kwp;

	for (kwp = keyword_table; kwp < keyword_table + size; kwp++)
	{
		if (strcmp(desired_word, *kwp) == 0)
			return kwp - keyword_table;
	}
	return -1;
}

/***********************
	程序 8.1 字符串复制
***********************/
void strting_copy(char *buffer, char const *string)
{
	while ((*buffer++ = *string++) != '\0')
		;
}

/******************************
	编程练习 7.11.6 支票面值
******************************/
void written_amount(unsigned int amount, char *buffer)
{
	;
}

/**********************************
	编程练习 7.11.5 打印格式字符
**********************************/
void my_printf()
{
	;
}

/***************************************
	编程练习 7.11.4 用可变参数列表求最大值
***************************************/
int max_value(int a, ...)
{
	va_list var_argument;
	int max_v = a;
	int current;

	va_start(var_argument, a);
	while ((current = va_arg(var_argument, int)) >= 0)
	{
		printf("%d\n", current);
		if (max_v < current)
			max_v = current;
	}
	va_end(var_argument);

	return max_v;
}


/******************************************
	编程练习 7.11.3 用迭代将字符串转换为整数
******************************************/
int ascii_to_integer(char *string)
{
	int result = 0;
	while (*string >= '0' && *string <= '9')
	{
		result *= 10;
		result += *string - '0';
		string++;
	}

	if (*string != '\0')	//未到字符串尾就执行到这里说明遇见非数字字符
		return 0;

	return result;
}

/************************************
	编程练习 7.11.2 用递归求最大公约数
************************************/
int gcd(int M, int N)
{
	int R;

	if (M <= 0 || N <= 0)
		return 0;

	if (M % N == 0)
		return N;
	if ((R = M % N) > 0)
		return gcd(N, R);
	return 0;
}
/*****************************************************
	编程练习 7.11.1 用递归求 Hermite polynomials 的值
*****************************************************/
int hermite (int n, int x)
{
	if ( n<= 0)
		return 1;
	if (n == 1)
		return 2 * x;
	return 2 * x * hermite(n-1, x) - 2 * (n-1) * hermite(n-2, x);
}

/**********************************
	程序 7.9 用可变参数列表求平均值
**********************************/
float average(int n_values, ...)
{
	va_list var_argument;
	int count;
	float sum = 0;

	va_start(var_argument, n_values);

	for (count = 0; count < n_values; count++)
		sum += va_arg(var_argument, int);

	va_end(var_argument);

	return sum / n_values;
}

/************************************
	程序 7.6 十进制整型转换为字符串 递归调用
************************************/
void binary_to_ascii_v1(unsigned int value)
{
	unsigned int quotient;
	quotient = value / 10;
	if (quotient != 0)
	{
		int_to_ascii(quotient);	//函数的参数总是去掉最低位
	}
	putchar(value % 10 + '0');	//打印当先函数参数的最低位
}

/************************
	短整型转换为字符串
************************/
int short_to_ascii(unsigned short n, char *buf)
{
	char temp[5];			//短整型的十进制形式最多5位
	int flag,i,j;

	temp[0] = n/10000;
	n %= 10000;
	temp[1] = n/1000;
	n %= 1000;
	temp[2] = n/100;
	n %= 100;
	temp[3] = n/10;
	temp[4] = n%10;

	flag = 0;
	j = 0;
	for (i=0;i<5;i++)
	{
		if (flag == 0)
		{
			if (temp[i] == 0)		//滤除高位的0
				continue;
		}
		flag = 1;
		buf[j++] = temp[i] + 0x30;
	}
	if (!flag)
		buf[j++] = 0x30;			//n为0

	buf[j] = '\0';
	return OK;
}

/******************************
	编程练习6.18.3 翻转字符串
******************************/
void reverse_string(char *str)
{
	char *last_char;

	for (last_char = str; *last_char != '\0'; last_char++)
		;
	last_char--;
	while (str < last_char)
	{
		char temp;

		temp = *str;
		*str++ = *last_char;
		*last_char-- = temp;
	}
}

/*************************************************
	编程练习6.18.2 在一个字符串中删除子字符串
*************************************************/
int delete_substring(char *str, char const *substr)
{
	char const *i, *j;
	char start = -1, tmp;
	unsigned char cnt, cpcnt;
	unsigned char str_len = strlen(str);
	unsigned char sub_len = strlen(substr);

	printf("str_len = %d\n", str_len);
	printf("sub_len = %d\n", sub_len);

	for (i = str; i < str + str_len; i++)
	{
		if (*i == *substr)
		{
			start = i - str;
			break;
		}
	}
	printf("start = %d\n", start);

	if (start >= 0)
	{
		for (j = substr; j< substr + sub_len;)
		{
			if (*i++ != *j++)
				break;
		}
		if (j == substr + sub_len)
		{
			cpcnt = str_len - sub_len;
			printf("cpcnt = %d\n", cpcnt);
			for (cnt = start; cnt < cpcnt; cnt++)
			{
				printf("str[%d] = %c\n", cnt, str[cnt]);
				printf("str[%d] = %c\n", cnt+sub_len, str[cnt+sub_len]);
				str[cnt] = str[cnt+sub_len];
			}
			printf("cnt = %d\n", cnt);
			str[cnt] = '\0';

		}
	}
	else
		printf("not found\n");
	return 0;
}

/*************************************************
	编程练习6.18.1 在一个字符串中查找第一个匹配的字符
*************************************************/
char const *stringpointbreak(char const *source, char const *chars)
{
	char const *i, *j;

	for (i = source; i < source + strlen(source); i++)
	{
		printf("i = %c\n", *i);
		for (j = chars; j < chars + strlen(chars); j++)
		{
			printf("j = %c\n", *j);
			if (*i == *j)
				return i;
		}
	}
	return NULL;
}

/*************************************
	程序6.2 在一组字符串中查找特定字符
*************************************/
int find_char_v1 (char **strings, char value)
{
	char *str;

	while ((str = *strings++) != NULL)
	{
		while (*str != '\0')
		{
			if (*str++ == value)
				return TRUE;
		}
	}
	return FALSE;
}

/*************************************
	程序6.3 在一组字符串中查找特定字符
*************************************/
int find_char_v2 (char **strings, int value)
{
	assert(strings != NULL);

	while (*strings != NULL)
	{
		while (**strings != '\0')
		{
			if (*(*strings)++ == value)
				return TRUE;
		}
		strings++;
	}
	return FALSE;
}

/******************************
	程序6.1 字符串长度
******************************/
size_t string_length (char *string)
{
    int length = 0;

    while (*string++ != '\0')
    {
        length += 1;
    }
    return length;
}

/******************************
	编程练习5.9.5 对整型值指定位操作
******************************/
int store_bit_field(int original_value, int value_to_store, unsigned starting_bit, unsigned ending_bit)
{
	unsigned mask = 0;
	short i;

	for (i = starting_bit; i >= ending_bit; i--)
	{
		mask |= 1 << i;
	}
	printf("mask = %x\n", mask);
	original_value &= ~mask;
	printf("original_value = %x\n", original_value);
	value_to_store <<= ending_bit;
	printf("value_to_store = %x\n", value_to_store);

	return (original_value | value_to_store);
}
/************************
	5.9.4 位数组
************************/
void set_bit(char bit_array[], unsigned bit_number)
{
	unsigned by = sizeof(char) * 8;
	unsigned nu = bit_number / by;
	unsigned re = by - bit_number % by;
	bit_array[nu] |= 1 << re;
}

void clear_bit(char bit_array[], unsigned bit_number)
{
	unsigned by = sizeof(char) * 8;
	unsigned nu = bit_number /by;
	unsigned re = by - bit_number % by;
	bit_array[nu] &= ~(1 << re);
}

void assign_bit(char bit_array[], unsigned bit_number, int value)
{
	if (value == 0)
		clear_bit(bit_array, bit_number);
	else
		set_bit(bit_array, bit_number);
}

int test_bit(char bit_array[], unsigned bit_number)
{
	unsigned by = sizeof(char) * 8;
	unsigned nu = bit_number /by;
	unsigned re = by - bit_number % by;

	if (bit_array[nu] & 1 << re)
		return TRUE;
	else
		return FALSE;
}

/************************
	5.9.3 翻转位的顺序
************************/
unsigned int reverse_bits(unsigned int value)
{
	unsigned int answer;
	unsigned int i;

	answer = 0;

	for (i=1; i!=0; i<<=1)
	{
		answer <<= 1;
		if (value & 1)
			answer |= 1;
		value >>= 1;
	}
	return answer;
}

/************************
	5.9.2 字符加密
************************/
void Encrypt(void)
{
	int c;
	while ((c = getchar()) != EOF)
	{
		if ((c >= 'a' && c <= 'm') || (c >='A' && c <= 'M'))
			c += 13;
		else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
			c -= 13;
		putchar(c);
	}
}

/*********************************
	5.9.1 大写字母转换为小写字母
*********************************/
void UpperToLowerCase()
{
	int c;
	while ((c = getchar()) != EOF)
	{
		if (c >= 'A' && c <= 'Z')
			c += 'a' - 'A';
		putchar(c);
	}
}

int TheLongestLine()
{
    char input[MAX_COLS];       //锟斤拷前锟斤拷锟斤拷锟斤拷
    char input_l[MAX_COLS];     //锟筋长锟斤拷一锟斤拷
    int len = 0;                //锟斤拷锟斤拷锟叫筹拷锟斤拷
    int len_max = 0;            //锟筋长锟叫筹拷锟斤拷
    int n = 0;

    while (gets(input) != NULL)
    {
        len = strlen(input);
        n += 1;
        printf("锟斤拷%d锟斤拷 锟斤拷锟斤拷为%d\n", n, len);

        if (len > len_max)
        {
            len_max = len;
            strcpy(input_l, input);
        }
    }
    printf("The longest is %s\n", input_l);
    return EXIT_SUCCESS;
}

/***************************
*	锟斤拷锟斤拷锟斤拷准锟斤拷锟斤拷锟斤拷校锟斤拷锟斤拷

***************************/
int ChectSum()
{
    int ch;
    signed char checksum = -1;

    while ((ch = getchar()) != EOF)
    {
        checksum += ch;

        if (ch == '\n')
        {
            printf("checksum = %d\n", checksum);
            checksum = -1;
        }
    }
    return EXIT_SUCCESS;
}

/***************************
*	锟斤拷锟斤拷准锟斤拷锟斤拷锟斤拷锟斤拷锟叫号猴拷锟斤拷锟斤拷

***************************/
int PrintLineNumber()
{
    int ch;
    int line;
    int at_beginning;

    line = 0;
    at_beginning = 1;

    while ((ch = getchar()) != EOF)
    {
        if (at_beginning == TRUE)
        {
            at_beginning = FALSE;
            line += 1;
            printf("%d ", line);
        }

        putchar(ch);

        //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟较ｏ拷锟斤拷一锟斤拷锟斤拷锟斤拷锟叫猴拷使锟斤拷
        if (ch == '\n')
            at_beginning = TRUE;
    }


    return EXIT_SUCCESS;
}

void copy_n (char dst[], char src[], int n)
{
	int dst_index, src_index;

	src_index = 0;

	for (dst_index = 0; dst_index < n; dst_index += 1)
	{
		dst[dst_index] = src[src_index];
		if (src[src_index] != 0)
			src_index += 1;
	}
}


int FindSameLines ()
{
	char current_line[128];
	char last_line[128];
	char result[128][128];
	int samelinecnt = 1, n = 0;
	unsigned char printed = 0;

	while (gets(current_line) != NULL)
	{
		//printf("last = %s current = %s\n",last_line, current_line);

		if (strcmp(current_line, last_line) == 0)
		{
			if (printed == 0)
			{
				samelinecnt += 1;
			}
			if (samelinecnt >= 2)
			{
				strcpy(result[n], current_line);
				n++;
				samelinecnt = 1;
				printed = 0xff;
			}
		}
		else
		{
			samelinecnt = 1;
			printed = 0;
		}
		strcpy(last_line, current_line);
	}
	printf("n = %d\n", n);
	int i = n;
	for (int n = 0; n < i; n++)
		printf("%s\n", result[n]);
	return 0;
}

/*******************************
	编程练习4.14.6 提取子字符串
*******************************/
int substr (char dst[], char src[], int start, int len)
{
	int dst_index, src_index;

	src_index = start;

	if (src_index > strlen(src) || src_index < 0 || len < 0 )
		return 0;

	for (dst_index = 0; dst_index < len; dst_index++, src_index++)
	{
		if (src[src_index] != 0)
			dst[dst_index] = src[src_index];
		else
			return (src_index - start);
	}
	return dst_index;
}

/*************************************
	编程练习4.14.7 删除字符串中多余空格
*************************************/
void deleteblank(char string[])
{
	int index, i;
	static int blankcnt;

	index = 0;
	while (index < strlen(string))
	{
		if (string[index] == ' ')
			blankcnt++;
		else
			blankcnt = 0;
		printf("index = %d blankcnt = %d \n", index, blankcnt);
		if (blankcnt >= 2)
		{
			i = index;
			while (i < strlen(string) - 1)
			{
				string[i] = string[i+1];
				i++;
			}
			string[i] = 0;
		}
		else
			index++;
	}
}

int BraceTest(int argc, char const *argv[])
{
    int ch;
    int braces = 0;

    while ((ch = getchar()) != EOF)
    {
        if (ch == '{')
            braces += 1;

        if (ch == '}')
        {
            if (braces == 0)
                printf("Extra closing brace !\n");
            else
                braces -= 1;
        }
    }

    if (braces > 0)
        printf("%d unmatched opening brace(s)\n", braces);

    return EXIT_SUCCESS;
}

char*  strtok_r_microsoft(char* string_org, const char* demial)
{
    static unsigned char* last; //保存分隔后剩余的部分
    unsigned char* str;         //返回的字符串
    const unsigned char* ctrl = (const unsigned char*)demial;//分隔字符

    //把分隔字符放到一个索引表中。定义32是因为ASCII字符表最多是0~255个，也是说用最大的255右移3位，也就是除以8一定会是32中的一个数。
    unsigned char map[32];
    int count;

    //把map全部清为0，之后相与的操作，与0的都为0
    for (count =0; count <32; count++)
    {
        map[count] = 0;
    }

    //把匹配字符放入表中
    //放入的算法是把匹配字符右移3位，相当于除以8，的数值 并上(加上)
    //匹配字符与7，得到低3位，得出的结果，是把1左移的位数。最大左移位数是7，也就是所表示的最大值是128,
    do
    {
        map[*ctrl >> 3] |= (1 << (*ctrl & 7));
    } while (*ctrl++);

    //原始字符串是否为空，如果为空表示第二次获取剩余字符的分隔部分。
    if (string_org)
    {
        str = (unsigned char*)string_org;
    }
    else
    {
        str = last;
    }

    //在表中查找是否有匹配的字符，如果有略过
    while ((map[*str >> 3] & (1 << (*str & 7)))  && *str)
    {
        str++;
    }

    //重置需要扫描的字符串
    string_org = (char*)str;

    //开始扫描
    for (;*str; str++)
    {
        if ( map[*str >> 3] & (1 << (*str & 7)))
        {
            *str++ = '\0';//当找到时，把匹配字符填为0，并且把str指向下一位。
            break; //退出循环
        }
    }

    last =str; // 把剩余字符串的指针保存到静态变量last中。

    if (string_org == (char*)str)
    {
        return NULL; //没有找到，也就是没有移动指针的位置，返回NULL
    }
    else
    {
        return string_org; //找到了，返回之前字符串的头指针
    }
}
