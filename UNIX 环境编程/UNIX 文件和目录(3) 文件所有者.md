# 函数

```
#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int lchown(const char *pathname, uid_t owner, gid_t group);
int fchownat(int dirfd, const char *pathname, uid_t owner, gid_t group, int flags);
```

`AT_SYMLINK_NOFOLLOW`

若 `_POSIX_CHOWN_RESTRICTED` 有效

超级用户可以修改文件的用户ID

普通用户可以修改拥有的文件的用户组ID

uid_t				st_uid;
gid_t				st_gid;

这两个成员是文件的性质

# 新建目录的所有权
