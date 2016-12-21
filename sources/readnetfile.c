/********************************************************************
	功能: 从网络上接受数据写入一个文件中
	来源: http://blog.csdn.net/leo115/article/details/8097143
*********************************************************************/
int main()  
{  
	int				sock;
	FILE			*fp;
	struct fd_set	fds;
	struct timeval	timeout = {3, 0};		//select等待3秒，3秒轮询，要非阻塞就置0
	char			buffer[256] = {0};		//256字节的接收缓冲区  
	/* 假定已经建立UDP连接，具体过程不写，简单，当然TCP也同理，主机ip和port都已经给定，要写的文件已经打开 
	sock=socket(...); 
	bind(...); 
	fp=fopen(...); */  
	while(1)  
	{  
		FD_ZERO(&fds);			//每次循环都要清空集合，否则不能检测描述符变化  
		FD_SET(sock, &fds);		//添加套接字描述符  
		FD_SET(fp, &fds);		//添加文件描述符
		maxfdp = sock > fp ? sock + 1 : fp + 1;		//文件描述符最大值加1  
		switch(select(maxfdp, &fds, &fds, NULL, &timeout))
		{
			case -1:
				exit(-1);
				break;			//select错误，退出程序  
			case 0:
				break;			//再次轮询  
			default:  
			if(FD_ISSET(sock, &fds)) //测试 sock 是否可读，即是否网络上有数据, 即描述符所在的那一位有效
			{
				recvfrom(sock, buffer, 256, .....);		//接受网络数据      
				if(FD_ISSET(fp, &fds))					//测试文件是否可写  
				fwrite(fp, buffer...);					//写入文件  
				//buffer清空;  
			}
		}
	}
}
