```
#include <sys/stat.h>
int stat(const char *restrict pathname, struct stat *restrict buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *restrict pathname, struct stat *restrict buf);
int fstatat(int fd, const char *restrict pathname, struct stat *restrict buf, int flag);
```
# 文件信息结构

```
struct stat{
	mode_t				st_mode;
	ino_t				st_ino;
	dev_t				st_dev;
	dev_t				st_rdev;
	nlink_t				st_nlink;
	uid_t				st_uid;
	gid_t				st_gid;
	off_t				st_size;
	struct timespec		st_atime;
	struct timespec		st_mtime;
	struct timespec		st_ctime;
	blksize_t			st_blksize;
	blkcnt_t			st_blocks;
}

struct timespec{
	time_t				tv_sec;
	long				tv_nsec;
}
```
| 成员 | 说明 |
| ---------- | - |
| st_mode    | 文件类型和权限 |
| st_ino     | i 节点号 |
| st_dev     | 设备号(文件系统) |
| st_rdev    | 设备号(特殊文件) |
| st_nlink   | 链接数 |
| st_uid     | 文件所有者的用户 ID |
| st_gid     | 文件的组所有者 ID |
| st_size    | 常规文件大小 |
| st_atime   | 最近访问时间 |
| st_mtime   | 最近修改时间 |
| st_ctime   | 最近文件状态修改时间 |
| st_blksize | 最优的 I/O 块大小 |
| st_blocks  | 分配的磁盘块的数量 |
