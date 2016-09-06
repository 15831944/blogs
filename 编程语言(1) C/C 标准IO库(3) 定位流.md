# 1. 函数接口

```
#include <stdio.h>

/* 文件偏移量存放在 long 类型中 */
long	ftell(FILE *fp);
int		fseek(FILE *fp, long offset, int whence);

void	rewind(FILE *fp);

/* 文件偏移量存放在 off_t 类型中 */
off_t	ftello(FILE *fp);
int		fseeko(FILE *fp, off_t offset, int whence);

/* 文件偏移量存放在 fpos_t 类型中 */
int		fgetpos(FILE *restrict fp, fpos_t *restrict pos);
int		fsetpos(FILE *fp, const fpos_t *pos);
```

# 2. 二进制文件

whence 取 SEEK_SET SEEK_CUR SEEK_END

offset 取任意整数表示的字节数

# 3. 文本文件

不同的系统可能以不同的格式存放文本文件

whence 只能取 SEEK_SET

offset 只能取 0 或对该文件的 ftell 的返回值
