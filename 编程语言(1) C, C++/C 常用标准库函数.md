# ctype.h

islower 函数和 inupper 函数判断字母大小写

在 scanf 函数的格式化字符串 "%c" 前面插入一个空格, 可以跳过输入中的空白字符, 以得到期望的字符 (Objective-C 程序设计 6.1.4节)

字符分类

字符转换

# stdio.h

gets
puts
getchar
putchar

scanf 依据指定格式扫描标准输入文件, 函数会一直等待标准输入文件内容, 返回成功赋值的数据项数

sprintf

# stdlib.h



# string.h

```
字符串长度

size_t strlen(char const *string);

// 不受限制的字符串函数(必须以 NUL 结尾)
char *strcpy  (char *dst, char const *src);
char *strcat   (char *dst, char const *src);
int     strcmp (char const *s1, char const *s2);

// 长度受限的字符串函数
char *strncpy (char *dst, char const *src, size_t len);
char *strncat  (char *dst, char const *src, size_t len);
int     strncmp (char const *s1, char const *s2, size_t len);

// 字符串查找函数
char *strchr(char const *str, int ch);
char *strrchr(char const *str, int ch);
char *strpbrk(char const *str, char const *group);
char *strstr(char const *s1, char const *s2);

// 高级字符串查找
size_t strspn(char const *str, char const *group);
size_t strcspn(char const *str, char const *group);

char *strtok(char *str, char const *sep);

// 错误信息
char *strerror (int error_number);

// 内存操作相关函数
void *memcpy  (void *dst, void const *src, size_t length);
void *memmove (void *dst, void const *src, size_t length);
void *memcmp  (void const *a, void const *b, size_t length);
void *memchr  (void const *a, int ch, size_t length);
void *memset  (void *a, int ch, size_t length);
```

# 系统调用

select或pselect函数

# 参考

1. [strtok()函数-doreen1162-ChinaUnix博客](http://blog.chinaunix.net/uid-11861796-id-2813603.html)
