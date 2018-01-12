/********************************************************************
	功能:  Linux 下监控键盘上是否有数据到来
	来源: http://blog.csdn.net/leo115/article/details/8097143
*********************************************************************/
#include <sys/time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

int main ()
{
    int				keyboard;
    int				ret,i;
    char			c;
    fd_set			readfd;
    struct timeval	timeout;

    keyboard = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    assert(keyboard > 0);

    while(1)
    {
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        FD_ZERO(&readfd);
        FD_SET(keyboard, &readfd);

        ///监控函数
        ret = select(keyboard + 1, &readfd, NULL, NULL, &timeout);
        if(ret == -1)   //错误情况
            cout<<"error"<<endl ;
        else if(ret)    //返回值大于0 有数据到来
            if(FD_ISSET(keyboard,&readfd))
            {
                i=read(keyboard,&c,1);
                if('\n'==c)
                    continue;
                printf("hehethe input is %c\n",c);
                if ('q'==c)
                    break;
            }
        else    //超时情况
        {
            cout<<"time out"<<endl;
            continue;
        }
    }
}
