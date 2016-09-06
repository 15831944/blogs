类型：

文件格式和转换 File formats and conventions 

结构体定义：

```
/* structure describing an open directory. */
typedef struct _dirdesc {
int     __dd_fd;      /* file descriptor associated with directory */
long    __dd_loc;     /* offset in current buffer */
long    __dd_size;    /* amount of data returned by getdirentries */
char    *__dd_buf;    /* data buffer */
int     __dd_len;     /* size of data buffer */
long    __dd_seek;    /* magic cookie returned by getdirentries */
long    __dd_rewind;  /* magic cookie for rewinding */
int     __dd_flags;   /* flags for readdir */
pthread_mutex_t __dd_lock; /* for thread locking */
struct _telldir *__dd_td; /* telldir position recording */
} DIR;

```

```c
struct dirent {
	ino_t      d_ino;    /* file number of entry */
	__uint16_t d_reclen; /* length of this record */
	__uint8_t  d_type;   /* file type, see below */
	__uint8_t  d_namlen;/* length of string in d_name */
	char    d_name[255 + 1];/* name must be no longer than this */
};
```

用法：

opendir()函数返回一个指向 DIR 结构的指针
readdir()和closedir()函数以 DIR结构的指针作为函数参数

readdir()函数返回一个指向 dirent 结构的指针
