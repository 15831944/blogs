# 口令文件 password

/etc/passwd

passwd 结构 

```
#include <pwd.h>
struct passwd *getpwuid(uid_t uid);
struct passwd *getpwnam(const char *name);
struct passwd *getpwent(void);
void setpwent(void);
void endpwent(void);
```

# 阴影口令 shadow password

/etc/shadow

spwd 结构

```
#include <shadow.h>
struct spwd *getspnam(const char *name);
struct spwd *getspent(void);
void setspent(void);
void endspent(void);
```

# 组文件 group

/etc/group

group 结构

```
#include <grp.h>
struct group *getgrgid(gid_t gid);
struct group *getgrnam(const char *name);
struct group *getgrent(void);
void setgrent(void);
void endgrent(void);
```

# 参考

UNIX 环境高级编程 6

















