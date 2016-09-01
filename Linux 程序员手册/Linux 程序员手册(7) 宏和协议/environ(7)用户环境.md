environ 是 UNIX 下的一个全局变量。
指向一个字符类型的指针数组。
每个数组元素是一个 "name=value" 形式的字符串。
数组以 NULL 指针结尾。
使用前应先声明：
```
extern char **environ;
```
有些类 UNIX 操作系统将环境变量作为main函数的第3个参数，但由于它其实是全局变量，因此没有必要。

与其相关的库函数有
```
clearenv(3)
getenv(3)
putenv(3)
setenv(3)
unsetenv(3)
```
环境变量举例如下：
                    
LOGNAME                                                                               
       The name of the logged-in user (used by some System-V derived programs).       
                                                                                      
HOME   A user's login directory, set by login(1) from the password file passwd(5).    
                                                                                      
LANG   The  name  of  a  locale to use for locale categories when not overridden by   
       LC_ALL or more specific environment  variables  like  LC_COLLATE,  LC_CTYPE,   
       LC_MESSAGES, LC_MONETARY, LC_NUMERIC, LC_TIME, cf.  locale(5).                 
                                                                                      
PATH   The  sequence of directory prefixes that sh(1) and many other programs apply   
       in searching for a file known by an incomplete pathname.  The  prefixes  are   
       separated by ':'.  (Similarly one has CDPATH used by some shells to find the   
       target of a change directory command, MANPATH used by man(1) to find  manual   
       pages, etc.)                                                                   
                                                                                      
PWD    The current working directory.  Set by some shells.                            
                                                                                      
SHELL  The pathname of the user's login shell.                                        
                                                                                      
TERM   The terminal type for which output is to be prepared.                          
                                                                                      
PAGER  The user's preferred utility to display text files.                           
