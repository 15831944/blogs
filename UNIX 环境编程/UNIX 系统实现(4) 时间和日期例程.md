# 1. 时间计量系统

时间计量系统有：世界时(UT)，国际原子时(TAI)，格林尼治标准时(GMT)，协调世界时(UTC)等等。

北京时间比 UTC 时间早8小时

UTC时间是1999年1月1日00:00

北京时间是1999年1月1日08:00

# 2. UNIX 系统时间值

UNIX 系统使用2种不同的时间值

## 1. 日历时间

1. 以协调世界时(UTC, Coordinated Universal Time)计量
2. 绝对时间，用于记录文件修改时间等
3. 系统基本数据类型 time_t

## 2. 进程时间

1. 又称 CPU 时间
2. 相对时间，用于度量进程使用 CPU 资源
3. 系统基本数据类型 clock_t

# 3. 时间和日期例程

参考 man page

```
#include <time.h>
void tzset(void);
time_t time(time_t *calptr);
time_t mktime(struct tm *tmptr);
struct tm *gmtime(const time_t *calptr);
struct tm *localtime(const time_t *calptr);
size_t strftime(char *restrict buf, size_t maxsize, const char *restrict format, const struct tm *restrict tmptr);
siet_t strftime_l(char *restrict buf, size_t maxsize, const char *restrict format, const struct tm *restrict tmptr, locale_t locale);

#include <sys/time.h>
int clock_gettime(clockid_t clock_id, struct timespec *tsp);
int clock_settime(clockid_t clock_id, const struct timespec *tsp);
int clock_getres(clockid_t clock_id, struct timespec *tsp);
int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
```

# 4. 示例

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char const *argv[])
{
	time_t         cal_time;	// 日历时间(s)
	struct timeval val_time;	// 日历时间(ns)
	struct tm     *brk_time;	// 分解时间
	struct timespec tsp;
	char buf[128];
	int rtn;

	time(&cal_time);
	printf("cal_time = %lds\n", cal_time);

	gettimeofday(&val_time, NULL);
	printf("val_time = %lds, %dns\n", val_time.tv_sec, val_time.tv_usec);

	brk_time = gmtime(&cal_time);
	printf("UTC_time =  %d-%d-%d %d:%d:%d\n", \
		brk_time->tm_year + 1900, brk_time->tm_mon + 1, brk_time->tm_mday, \
		brk_time->tm_hour, brk_time->tm_min, brk_time->tm_sec);

	printf("cal_time1 = %lds\n", mktime(brk_time));

	brk_time = localtime(&cal_time);
	printf("Local_time =  %d-%d-%d %d:%d:%d\n", \
		brk_time->tm_year + 1900, brk_time->tm_mon + 1, brk_time->tm_mday, \
		brk_time->tm_hour, brk_time->tm_min, brk_time->tm_sec);

	printf("cal_time2 = %lds\n", mktime(brk_time));

	rtn = strftime(buf, 128, "year = %Y month = %B day = %d week = %A", brk_time);
	printf("rtn =%d %s\n",rtn, buf);

	strcpy(buf,"2001-02-03 4:5:6");
	strptime(buf, "%F %T", brk_time);
	printf("str_time =  %d-%d-%d %d:%d:%d\n", \
		brk_time->tm_year + 1900, brk_time->tm_mon + 1, brk_time->tm_mday, \
		brk_time->tm_hour, brk_time->tm_min, brk_time->tm_sec);
	return 0;
}
```

## 1. 输出结果

```
cal_time = 1468111161s
val_time = 1468111161s, 719666ns
UTC_time =  2016-7-10 0:39:21
cal_time1 = 1468082361s
Local_time =  2016-7-10 8:39:21
cal_time2 = 1468111161s
rtn =47 year = 2016 month = July day = 10 week = Sunday
str_time =  2001-2-3 4:5:6
```

## 2. 分析

1. time 函数打印1970年至今的秒数，且是以本地时间计算的
2. gettimeofday 函数同理，但是具有更高的精度，纳秒级
3. 从分解时间可以看到，当地时间比标准时间快了8个小时
4. 可以用指定的字符串格式设置时间


# 5. 参考

UNIX 环境高级编程 1.10 6.10